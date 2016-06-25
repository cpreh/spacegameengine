/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/egl/wayland/window.hpp>
#include <awl/backends/wayland/window/object.hpp>
#include <awl/window/event/processor.hpp>
#include <awl/window/event/resize.hpp>
#include <awl/window/event/resize_callback.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-egl-core.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::wayland::window::window(
	awl::backends::wayland::window::object &_window
)
:
	window_{
		_window
	},
	resize_connection_{
		_window.processor().resize_callback(
			awl::window::event::resize_callback{
				[
					this
				](
					awl::window::event::resize const &_resize
				)
				{
					::wl_egl_window_resize(
						window_.get(),
						fcppt::cast::to_signed(
							_resize.dim().w()
						),
						fcppt::cast::to_signed(
							_resize.dim().h()
						),
						0,
						0
					);
				}
			}
		)
	}
{
}


sge::opengl::egl::wayland::window::~window()
{
}

wl_egl_window *
sge::opengl::egl::wayland::window::get() const
{
	return
		window_.get();
}
