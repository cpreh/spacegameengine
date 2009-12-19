/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_WINDOWS_STATE_HPP_INCLUDED
#define SGE_OPENGL_WINDOWS_STATE_HPP_INCLUDED

#include "../viewport_fun.hpp"
#include "../wgl/context.hpp"
#include "../wgl/current.hpp"
#include <sge/windows/gdi_device.hpp>
#include <sge/windows/window_fwd.hpp>
#include <sge/renderer/adapter_type.hpp>
#include <sge/window/instance_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{
class parameters;
}
namespace opengl
{
namespace windows
{

class state {
	FCPPT_NONCOPYABLE(state)
public:
	state(
		renderer::parameters const &,
		renderer::adapter_type,
		window::instance_ptr,
		view_port_fun const &);

	void swap_buffers();
	void reset_viewport();
private:
	sge::windows::window_ptr const wnd;
	sge::windows::gdi_device const hdc;
	wgl::context             const context;
	wgl::current             const current;
};

}
}
}

#endif
