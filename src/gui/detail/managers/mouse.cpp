/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/gui/detail/managers/mouse.hpp>
#include <sge/gui/events/mouse_click.hpp>
#include <sge/gui/events/mouse_enter.hpp>
#include <sge/gui/events/mouse_leave.hpp>
#include <sge/gui/events/mouse_move.hpp>
#include <sge/gui/widgets/base.hpp>
#include <sge/gui/cursor/base.hpp>
#include <sge/gui/sprite/unit.hpp>
#include <sge/gui/sprite/point.hpp>
#include <sge/gui/exception.hpp>
#include <sge/gui/log.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/button_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/texture/part_raw.hpp>
#include <fcppt/math/box/contains_point.hpp>
#include <fcppt/math/box/output.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/algorithm/ptr_container_erase.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert.hpp>
#include <boost/foreach.hpp>

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sge::gui::global_log(),
		FCPPT_TEXT("managers: mouse")
	)
);

sge::gui::sprite::point const
key_to_mouse_coords(
	sge::input::mouse::axis_event const &k
)
{
	switch(
		k.axis()
	)
	{
	case sge::input::mouse::axis::x:
		return sge::gui::sprite::point(
			static_cast<sge::gui::sprite::unit>(k.axis_value()),
			static_cast<sge::gui::sprite::unit>(0)
		);
	case sge::input::mouse::axis::y:
		return sge::gui::sprite::point(
			static_cast<sge::gui::sprite::unit>(0),
			static_cast<sge::gui::sprite::unit>(k.axis_value())
		);
	default:
		return sge::gui::sprite::point::null(); // TODO?
	}
}

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

sge::gui::detail::managers::mouse::mouse(
	input::mouse::device_ptr const _mouse,
	cursor::base_ptr _cursor
)
:
	widgets(),
	axis_connection(
		_mouse->axis_callback(
	  		std::tr1::bind(
				&mouse::axis_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	button_connection(
		_mouse->button_callback(
			std::tr1::bind(
				&mouse::button_callback,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	cursor_(_cursor),
	focus(0),
	dirty_(false)
{
}

void sge::gui::detail::managers::mouse::resize(
	widgets::base &,
	dim const &)
{
	dirty_ = true;
}

void sge::gui::detail::managers::mouse::reposition(
	widgets::base &,
	point const &)
{
	dirty_ = true;
}

void sge::gui::detail::managers::mouse::add(widgets::base &w)
{
	// We only store top level widgets as "starting points" for our focus search
	if (!w.has_parent())
		widgets.push_back(&w);

	// It could be the case that the newly added widgets::base is below the cursor and should
	// thus get the focus, so we recalculate
	dirty_ = true;
}

void sge::gui::detail::managers::mouse::update()
{
	if (dirty_)
	{
		recalculate_focus();
		dirty_ = false;
	}
}

void sge::gui::detail::managers::mouse::activation(
	widgets::base &,
	activation_state::type)
{
	dirty_ = true;
}

void sge::gui::detail::managers::mouse::remove(widgets::base &w)
{
	// We've got a problem if
	// (a) the currently focused widgets::base should be deleted, or...
	// (b) one of its children
	if (focus == &w || w.has_child(*focus))
	{
		// If so, we start at the focused widgets::base and traverse the tree upwards until
		// we reach the widget's parent (it could be 0).
		widgets::base *const parent = w.has_parent() ? &(w.parent_widget()) : 0;
		while (focus != parent)
		{
			focus->process_mouse_leave(events::mouse_leave());
			focus = focus->has_parent() ? &(focus->parent_widget()) : 0;
		}
	}

	// And if it's a top level widget, we have to delete it from our widgets list
	if (!w.has_parent())
	{
		FCPPT_ASSERT(
			utility::ptr_find(widgets.begin(),widgets.end(),&w) != widgets.end());
		fcppt::algorithm::ptr_container_erase(
			widgets,
			&w);
	}
}

void sge::gui::detail::managers::mouse::recalculate_focus()
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("in top level recalculate_focus"));

	point const click_point(
		fcppt::math::vector::structure_cast<
			point
		>(
			cursor_->pos()
		)
	);

	if (focus)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << FCPPT_TEXT("a widgets::base currently has the focus, recalculating"));

		focus = recalculate_focus(*focus,click_point);
	}

	if (!focus)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ <<
				FCPPT_TEXT("no widgets::base currently has the focus, so letting it recalculate"));

		BOOST_FOREACH(widgets::base &w,widgets)
		{
			FCPPT_LOG_DEBUG(
				mylogger,
				fcppt::log::_ << FCPPT_TEXT("checking if ") << w.screen_area()
				        << FCPPT_TEXT(" contains ") << click_point);

			if (w.activation() == activation_state::active &&
			    contains_point(w.screen_area(),click_point))
			{
				w.process_mouse_enter(events::mouse_enter(click_point));
				focus = recalculate_focus(w,click_point);
				return;
			}
		}
	}
}

void sge::gui::detail::managers::mouse::z(
	widgets::base &w,
	depth_type const _z)
{

}

void
sge::gui::detail::managers::mouse::axis_callback(
	input::mouse::axis_event const &k
)
{
	cursor_->pos(
		cursor_->pos()
		+ key_to_mouse_coords(k)
	);

	recalculate_focus();
}

void
sge::gui::detail::managers::mouse::button_callback(
	input::mouse::button_event const &k
)
{
	if (!focus)
		return;

	focus->process_mouse_click(
		events::mouse_click(
			fcppt::math::vector::structure_cast<point>(
				cursor_->pos()
			),
			k
		)
	);
}


sge::gui::widgets::base *sge::gui::detail::managers::mouse::recalculate_focus(
	widgets::base &w,
	point const &mouse_click)
{
	// Pointer is no longer inside widgets::base area
	if (!contains_point(w.screen_area(),mouse_click) ||
	    !active(w))
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << FCPPT_TEXT("mouse no longer inside widget, sending leave"));

		w.process_mouse_leave(events::mouse_leave());

		// Pointer is in "free space" now
		if (!w.has_parent())
			return 0;

		// Recalculate from the parent on
		return recalculate_focus(w.parent_widget(),mouse_click);
	}

	widgets::base *const new_focus = do_recalculate_focus(w,mouse_click);

	if (new_focus == &w)
	{
		FCPPT_LOG_DEBUG(
			mylogger,
			fcppt::log::_ << FCPPT_TEXT("focus hasn't changed, sending mouse_move"));
		w.process_mouse_move(events::mouse_move(mouse_click));
	}
	return new_focus;
}

sge::gui::widgets::base *sge::gui::detail::managers::mouse::do_recalculate_focus(
	widgets::base &w,
	point const &p)
{
	BOOST_FOREACH(widgets::base &child,w.children())
	{
		if (child.activation() == activation_state::active &&
		    contains_point(child.screen_area(),p))
		{
			FCPPT_LOG_DEBUG(
				mylogger,
				fcppt::log::_ << FCPPT_TEXT("a child has the focus, sending enter and descending"));
			child.process_mouse_enter(events::mouse_enter(p));
			return do_recalculate_focus(child,p);
		}
	}

	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ << FCPPT_TEXT("no child has the focus, doing nothing"));
	return &w;
}
