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


#include <sge/opengl/egl/wayland/window_holder.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/wayland/window/object.hpp>
#include <awl/window/dim.hpp>
#include <awl/window/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-egl-core.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::wayland::window_holder::window_holder(
	awl::window::object const &_window
)
:
	window_{
		::wl_egl_window_create(
			fcppt::cast::dynamic_exn<
				awl::backends::wayland::window::object const &
			>(
				_window
			).surface(),
			fcppt::cast::to_signed(
				_window.size().w()
			),
			fcppt::cast::to_signed(
				_window.size().h()
			)
		)
	}
{
	if(
		window_
		==
		nullptr
	)
		throw
			sge::renderer::exception{
				FCPPT_TEXT("Cannot create wayland egl window")
			};
}


sge::opengl::egl::wayland::window_holder::~window_holder()
{
	::wl_egl_window_destroy(
		window_
	);
}

wl_egl_window *
sge::opengl::egl::wayland::window_holder::get() const
{
	return
		window_;
}
