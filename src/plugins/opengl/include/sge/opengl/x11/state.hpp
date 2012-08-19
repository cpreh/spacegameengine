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


#ifndef SGE_OPENGL_X11_STATE_HPP_INCLUDED
#define SGE_OPENGL_X11_STATE_HPP_INCLUDED

#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/device_state/object.hpp>
#include <sge/opengl/device_state/scoped_current.hpp>
#include <sge/opengl/x11/context.hpp>
#include <sge/opengl/xrandr/state.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <sge/renderer/parameters/object_fwd.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace x11
{

class state
:
	public sge::opengl::device_state::object
{
	FCPPT_NONCOPYABLE(
		state
	);
public:
	state(
		sge::opengl::context::system::object &,
		sge::renderer::parameters::object const &,
		awl::backends::x11::window::object &
	);

	~state();
private:
	void
	begin_rendering();

	void
	swap_buffers();

	sge::renderer::display_mode::object const
	display_mode() const;

	awl::backends::x11::window::object &window_;

	sge::opengl::x11::context context_;

	sge::opengl::device_state::scoped_current const scoped_current_;

	sge::opengl::xrandr::state const xrandr_state_;
};

}
}
}

#endif
