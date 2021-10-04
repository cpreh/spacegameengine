//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_WAYLAND_WINDOW_HOLDER_HPP_INCLUDED
#define SGE_OPENGL_EGL_WAYLAND_WINDOW_HOLDER_HPP_INCLUDED

#include <awl/window/object_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-egl-core.h>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::egl::wayland
{

class window_holder
{
	FCPPT_NONMOVABLE(
		window_holder
	);
public:
	explicit
	window_holder(
		awl::window::object_ref
	);

	~window_holder();

	[[nodiscard]]
	wl_egl_window *
	get() const;
private:
	wl_egl_window *const window_;
};

}

#endif
