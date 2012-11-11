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


#ifndef SGE_OPENGL_X11_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_X11_CONTEXT_HPP_INCLUDED

#include <sge/opengl/device_state/context.hpp>
#include <sge/opengl/glx/context_scoped_ptr.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace x11
{

class context
:
	public sge::opengl::device_state::context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	explicit
	context(
		awl::backends::x11::window::object &
	);

	~context();

	void
	activate();

	void
	deactivate();

	void
	swap_buffers();
private:
	awl::backends::x11::window::object &window_;

	awl::backends::x11::display &display_;

	sge::opengl::glx::context_scoped_ptr const glx_context_;
};

}
}
}


#endif
