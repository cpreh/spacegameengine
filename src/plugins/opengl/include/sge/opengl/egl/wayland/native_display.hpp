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


#ifndef SGE_OPENGL_EGL_WAYLAND_NATIVE_DISPLAY_HPP_INCLUDED
#define SGE_OPENGL_EGL_WAYLAND_NATIVE_DISPLAY_HPP_INCLUDED

#include <sge/opengl/egl/native_display.hpp>
#include <sge/opengl/egl/native_window_unique_ptr.hpp>
#include <awl/backends/wayland/system/object_fwd.hpp>
#include <awl/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace egl
{
namespace wayland
{

class native_display
:
	public sge::opengl::egl::native_display
{
	FCPPT_NONCOPYABLE(
		native_display
	);
public:
	explicit
	native_display(
		awl::backends::wayland::system::object &
	);

	~native_display()
	override;
private:
	EGLNativeDisplayType
	get() const
	override;

	sge::opengl::egl::native_window_unique_ptr
	create_native_window(
		awl::window::object &
	)
	override;

	EGLNativeDisplayType const display_;
};

}
}
}
}

#endif
