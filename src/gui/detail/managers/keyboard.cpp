/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../../utility/ptr_find.hpp"
#include <sge/gui/detail/managers/keyboard.hpp>
#include <sge/gui/events/key.hpp>
#include <sge/gui/events/keyboard_enter.hpp>
#include <sge/gui/events/keyboard_leave.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/log.hpp>
#include <sge/gui/exception.hpp>
#include <sge/input/system.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/classification.hpp>
#include <sge/input/key_pair.hpp>
#include <fcppt/math/almost_zero.hpp>
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/object.hpp>
#include <sge/log/headers.hpp>
#include <fcppt/assert.hpp>
#include <boost/next_prior.hpp>
#include <tr1/functional>
#include <algorithm>

namespace
{

sge::log::object mylogger(
	sge::log::parameters::inherited(
		sge::gui::global_log(),
		FCPPT_TEXT("managers: keyboard")
	)
);

bool active(sge::gui::widgets::base const &w)
{
	switch (w.activation())
	{
		case sge::gui::activation_state::active:
			if (!w.has_parent())
				return true;
			return active(w.parent_widget());
		case sge::gui::activation_state::inactive:
			return false;
	}
	throw sge::gui::exception(FCPPT_TEXT("missed an activation state"));
}
}

sge::gui::detail::managers::keyboard::keyboard(sge::input::system_ptr const is)
:
	input_filter(is),
	ic(
		input_filter.register_callback(
			std::tr1::bind(
				&keyboard::input_callback,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2,
				false
			)
		)
	),
	irc(
		input_filter.register_repeat_callback(
			std::tr1::bind(
				&keyboard::repeat_callback,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		)
	)
{
}

// Here, we could add a keyboard_enter event to the first added widget, but the function
// below is called from a base class constructor, so widget::process(keyboard_enter)
// is called instead of most_derived::process(keyboard_enter), so the policy is: No
// widgets::base initially has the focus.
void sge::gui::detail::managers::keyboard::add(widgets::base &w)
{
	/* TODO: think about this
	BOOST_FOREACH(widgets::base &v,w.children())
		add(v);
		*/

	if (w.keyboard_focus() == keyboard_focus::ignore)
		return;

	FCPPT_LOG_DEBUG(
		mylogger,
		log::_ << FCPPT_TEXT("adding widget"));

	FCPPT_ASSERT(
		utility::ptr_find(widgets.begin(),widgets.end(),&w)
			== widgets.end());

	widgets.push_back(&w);
}

void sge::gui::detail::managers::keyboard::activation(
	widgets::base &w,
	activation_state::type const a)
{
	if (!focus)
		return;

	if (!w.has_child(**focus) && &(**focus) != &w)
		return;

	if (a == activation_state::active)
		return;

	(*focus)->process_keyboard_leave(events::keyboard_leave());
	focus.reset();
}

void sge::gui::detail::managers::keyboard::request_focus(widgets::base &w)
{
	widget_container::iterator wi = utility::ptr_find(
			widgets.begin(),
			widgets.end(),&w);

	FCPPT_ASSERT_MESSAGE(
		wi != widgets.end(),
		FCPPT_TEXT("a widgets::base requested the keyboard focus which cannot receive keys"));

	// Widget already has the focus?
	if (focus && *focus == wi)
		return;

	switch_focus(wi);
}

void sge::gui::detail::managers::keyboard::remove(widgets::base &w)
{
	if (w.keyboard_focus() == keyboard_focus::ignore)
		return;

	widget_container::iterator wi = utility::ptr_find(
			widgets.begin(),
			widgets.end(),&w);

	FCPPT_ASSERT(wi != widgets.end());

	// the widgets::base to delete has the focus? then reset focus
	if (focus && *focus == wi)
		focus.reset();
/* old (alternative) behaviour was to take the next possible widget
		switch_focus(
			boost::next(*focus) == widgets.end()
				? widgets.begin()
				: boost::next(*focus));
				*/

	widgets.erase(wi);
}

void sge::gui::detail::managers::keyboard::cycle_focus()
{
	if (widgets.empty())
		return;

	// If no widgets::base currently has the focus, take the first (active) one on the
	// list
	if (!focus)
	{
		for (widget_container::iterator i = widgets.begin();
		     i != widgets.end();
				 ++i)
		{
			if (active(*i))
			{
				switch_focus(i);
				break;
			}
		}
		return;
	}

	FCPPT_ASSERT((*focus)->activation() == activation_state::active);

	widget_container::iterator next = boost::next(*focus);
	if (next == widgets.end())
		next = widgets.begin();

	while (!active(*next))
	{
		++next;
		if (next == widgets.end())
			next = widgets.begin();
	}

	switch_focus(next);
}


// This is called by manager whenever a widgets::base changes its behaviour towards the
// keyboard focus. If a widgets::base decides not to accept the focus anymore, we have to
// delete it and possibly nominate a new focused widget
void sge::gui::detail::managers::keyboard::keyboard_focus(
	widgets::base &w,
	keyboard_focus::type const n)
{
	switch (n)
	{
		case keyboard_focus::ignore:
		{
			widget_container::iterator wi = utility::ptr_find(
					widgets.begin(),
					widgets.end(),&w);

			// The widgets::base ignores keyboard focus and it never accepted it?
			// then we can return
			if (wi == widgets.end())
				return;

			// The widgets::base to delete has the focus? then take the next one
			if (focus && *focus == wi)
			{
				// ...if there is a next one
				if (widgets.size() != 1)
				{
					switch_focus(
						boost::next(*focus) == widgets.end()
							? widgets.begin()
							: boost::next(*focus));
				}
			}

			widgets.erase(wi);
		}
		break;
		case keyboard_focus::receive:
		{
			FCPPT_LOG_DEBUG(
				mylogger,
				log::_ << FCPPT_TEXT("adding widgets::base after focus change"));
			widget_container::iterator wi = utility::ptr_find(
					widgets.begin(),
					widgets.end(),&w);

			// The widgets::base has the focus and has had it before? Then
			// there's nothing to do
			if (wi != widgets.end())
				return;

			add(w);
		}
		break;
	}
}

void sge::gui::detail::managers::keyboard::repeat_callback(
	input::key_type const &k,
	input::modifier::states const &s)
{
	input_callback(
		input::key_pair(
			k,
			static_cast<input::key_state>(1)),
		s,
		true);
}

void sge::gui::detail::managers::keyboard::input_callback(
	input::key_pair const &k,
	input::modifier::states const &s,
	bool const repeated)
{
	if (widgets.empty())
		return;

	if (input::is_mouse_axis(k.key().code()) || input::is_mouse_button(k.key().code()))
		return;

	if (focus)
	{
		if ((*focus)->process_key(events::key(k,s,repeated)) == key_handling::ignore)
			return;
	}

	if (k.key().code() == sge::input::kc::key_tab)
	{
		if (!sge::fcppt::math::almost_zero(k.value()))
			cycle_focus();
		return;
	}
}

void sge::gui::detail::managers::keyboard::switch_focus(widget_container::iterator n)
{
	FCPPT_LOG_DEBUG(mylogger,log::_ << FCPPT_TEXT("switching focus"));
	if (focus)
		(*focus)->process_keyboard_leave(events::keyboard_leave());
	focus = n;
	(*focus)->process_keyboard_enter(events::keyboard_enter());
}
