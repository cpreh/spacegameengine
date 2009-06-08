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


#include <sge/gui/widgets/buttons/base.hpp>
#include <sge/gui/widgets/parameters.hpp>
#include <sge/gui/events/key.hpp>
#include <sge/gui/events/mouse_click.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/widgets/log.hpp>
#include <sge/input/key_type.hpp>
#include <sge/input/key_code.hpp>
#include <sge/math/rect/basic_impl.hpp>

namespace
{
sge::gui::logger mylogger(
	sge::gui::widgets::global_log(),
	SGE_TEXT("buttons::base"),
	false);
}


bool
sge::gui::widgets::buttons::base::mouse_over() const
{
	return mouse_over_;
}
	
bool
sge::gui::widgets::buttons::base::key_over() const
{
	return key_over_;
}

void sge::gui::widgets::buttons::base::process(events::mouse_enter const &)
{
	mouse_over_ = true;
	parent_manager().dirty(*this,rect(point::null(),size()));
}

void sge::gui::widgets::buttons::base::process(events::mouse_leave const &)
{
	mouse_over_ = false;
	parent_manager().dirty(*this,rect(point::null(),size()));
}

void sge::gui::widgets::buttons::base::process(events::mouse_click const &c)
{
	if (c.value().value())
		clicked_();
}

sge::gui::key_handling::type sge::gui::widgets::buttons::base::process(
	events::key const &k)
{
	if (k.value().key().code() == input::kc::key_return)
	{
		clicked_();
		return key_handling::ignore;
	}
	return key_handling::process;
}

void sge::gui::widgets::buttons::base::process(events::keyboard_enter const &)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_enter"));
	key_over_ = true;
	parent_manager().dirty(*this,rect(point::null(),size()));
}

void sge::gui::widgets::buttons::base::process(events::keyboard_leave const &)
{
	SGE_LOG_DEBUG(mylogger,log::_1 << SGE_TEXT("got keyboard_leave"));
	key_over_ = false;
	parent_manager().dirty(*this,rect(point::null(),size()));
}

sge::signal::auto_connection sge::gui::widgets::buttons::base::register_clicked(
	clicked_fn const &_clicked)
{
	return clicked_.connect(_clicked);
}

sge::gui::widgets::buttons::base::~base() {}

sge::gui::widgets::buttons::base::base(
	parent_data const &_parent,
	parameters _params)
:
	widgets::base(
		_parent,
		_params
			.keyboard_focus(
				keyboard_focus::receive)),
	mouse_over_(false),
	key_over_(false)
{
}
