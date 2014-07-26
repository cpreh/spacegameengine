/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/window/dim.hpp>
#include <sge/window/object.hpp>
#include <awl/event/processor_fwd.hpp>
#include <awl/window/object.hpp>
#include <awl/window/event/processor_fwd.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::window::object::object(
	awl::window::object &_awl_object,
	awl::window::event::processor &_awl_window_processor,
	awl::event::processor &_awl_processor
)
:
	awl_object_(
		_awl_object
	),
	awl_window_processor_(
		_awl_window_processor
	),
	attachment_(
		_awl_processor,
		awl_window_processor_
	)
{
}

sge::window::object::~object()
{
}

sge::window::dim const
sge::window::object::size() const
{
	return
		fcppt::math::dim::structure_cast<
			sge::window::dim
		>(
			awl_object_.size()
		);
}

void
sge::window::object::show()
{
	awl_object_.show();
}

awl::window::object &
sge::window::object::awl_object() const
{
	return
		awl_object_;
}

awl::window::event::processor &
sge::window::object::awl_window_event_processor() const
{
	return
		awl_window_processor_;
}
