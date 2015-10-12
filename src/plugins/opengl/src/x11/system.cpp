/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/platform/device_state_unique_ptr.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/opengl/x11/device_state.hpp>
#include <sge/opengl/x11/system.hpp>
#include <sge/opengl/xrandr/create_system.hpp>
#include <sge/opengl/xrandr/system.hpp>
#include <sge/opengl/xrandr/system_unique_ptr.hpp>
#include <sge/renderer/caps/device_count.hpp>
#include <sge/renderer/device/index.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <awl/backends/x11/system/object.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/backends/x11/window/event/processor.hpp>
#include <awl/window/object.hpp>
#include <awl/window/event/processor.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/static_downcast.hpp>


sge::opengl::x11::system::system(
	awl::backends::x11::system::object &_awl_system
)
:
	xrandr_system_(
		sge::opengl::xrandr::create_system(
			_awl_system.display()
		)
	)
{
}

sge::opengl::x11::system::~system()
{
}

sge::renderer::caps::device_count
sge::opengl::x11::system::device_count() const
{
	// TODO:
	return
		sge::renderer::caps::device_count(
			1u
		);
}

sge::renderer::display_mode::container
sge::opengl::x11::system::display_modes(
	sge::renderer::device::index const _index
) const
{
	// TODO:
	return
		sge::renderer::display_mode::container();
}

sge::opengl::platform::device_state_unique_ptr
sge::opengl::x11::system::create_device_state(
	sge::renderer::display_mode::optional_object const &_display_mode,
	awl::window::object &_window,
	awl::window::event::processor &_processor
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::platform::device_state
		>(
			fcppt::make_unique_ptr<
				sge::opengl::x11::device_state
			>(
				fcppt::optional_bind_construct(
					xrandr_system_,
					[](
						sge::opengl::xrandr::system_unique_ptr const &_system
					)
					-> sge::opengl::xrandr::system &
					{
						return
							*_system;
					}
				),
				_display_mode,
				fcppt::cast::static_downcast<
					awl::backends::x11::window::object &
				>(
					_window
				),
				fcppt::cast::static_downcast<
					awl::backends::x11::window::event::processor &
				>(
					_processor
				)
			)
		);
}
