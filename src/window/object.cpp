/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <awl/window/instance.hpp>
#include <awl/window/event/processor_fwd.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


sge::window::object::object(
	awl::window::instance &_instance,
	awl::window::event::processor &_window_processor,
	awl::event::processor &_processor
)
:
	instance_(
		_instance
	),
	window_processor_(
		_window_processor
	),
	attachment_(
		_processor,
		window_processor_
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
			instance_.size()
		);
}

void
sge::window::object::show()
{
	instance_.show();
}

awl::window::instance &
sge::window::object::awl_instance() const
{
	return instance_;
}

awl::window::event::processor &
sge::window::object::awl_window_event_processor() const
{
	return window_processor_;
}
