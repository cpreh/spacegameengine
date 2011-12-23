/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_X11_STATE_HPP_INCLUDED
#define SGE_OPENGL_X11_STATE_HPP_INCLUDED

#include <sge/opengl/device_state.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/glx/context_ptr.hpp>
#include <sge/opengl/glx/current.hpp>
#include <sge/opengl/x11/resolution/instance_fwd.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/window/instance_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sge
{
namespace opengl
{
namespace x11
{

class state
:
	public opengl::device_state
{
	FCPPT_NONCOPYABLE(
		state
	);
public:
	state(
		opengl::context::object &,
		renderer::parameters const &,
		renderer::adapter,
		awl::backends::x11::window::instance &
	);

	~state();

	void
	swap_buffers();
private:
	awl::backends::x11::window::instance &window_;

	awl::backends::x11::display &display_;

	glx::context_ptr const context_;

	glx::current const current_;

	fcppt::scoped_ptr<
		resolution::instance
	> resolution_;
};

}
}
}

#endif
