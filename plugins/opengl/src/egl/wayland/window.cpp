//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
