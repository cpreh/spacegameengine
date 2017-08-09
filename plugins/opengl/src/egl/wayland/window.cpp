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
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <awl/window/event/base.hpp>
#include <awl/window/event/resize.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-egl-core.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::wayland::window::window(
	sge::window::object &_window
)
:
	holder_{
		_window.awl_object()
	},
	resize_connection_{
		_window.event_handler(
			sge::window::event_function{
				[
					this
				](
					awl::window::event::base const &_event
				)
				{
					fcppt::optional::maybe_void(
						fcppt::cast::dynamic<
							awl::window::event::resize const
						>(
							_event
						),
						[
							this
						](
							fcppt::reference<
								awl::window::event::resize const
							> const _resize
						)
						{
							::wl_egl_window_resize(
								this->holder_.get(),
								fcppt::cast::to_signed(
									_resize.get().dim().w()
								),
								fcppt::cast::to_signed(
									_resize.get().dim().h()
								),
								0,
								0
							);
						}
					);

					return
						awl::event::container{};
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
		holder_.get();
}
