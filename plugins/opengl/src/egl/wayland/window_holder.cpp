//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/egl/wayland/window_holder.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/wayland/window/object.hpp>
#include <awl/window/dim.hpp>
#include <awl/window/object.hpp>
#include <awl/window/object_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-egl-core.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::wayland::window_holder::window_holder(
	awl::window::object_ref const _window
)
:
	window_{
		::wl_egl_window_create(
			fcppt::cast::dynamic_exn<
				awl::backends::wayland::window::object const &
			>(
				_window.get()
			).surface(),
			fcppt::cast::to_signed(
				_window.get().size().w()
			),
			fcppt::cast::to_signed(
				_window.get().size().h()
			)
		)
	}
{
	if(
		window_
		==
		nullptr
	)
	{
		throw
			sge::renderer::exception{
				FCPPT_TEXT("Cannot create wayland egl window")
			};
	}
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
