//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_EGL_WAYLAND_WINDOW_HPP_INCLUDED
#define SGE_OPENGL_EGL_WAYLAND_WINDOW_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <wayland-egl-core.h>
#include <fcppt/config/external_end.hpp>
#define SGE_OPENGL_EGL_WAYLAND_WINDOW_HPP_EGL_CORE_ON_TOP
#include <sge/opengl/egl/wayland/window_holder.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace opengl
{
namespace egl
{
namespace wayland
{

class window
{
	FCPPT_NONCOPYABLE(
		window
	);
public:
	explicit
	window(
		sge::window::object &
	);

	~window();

	wl_egl_window *
	get() const;
private:
	sge::opengl::egl::wayland::window_holder const holder_;

	fcppt::signal::auto_connection const resize_connection_;
};

}
}
}
}

#endif
