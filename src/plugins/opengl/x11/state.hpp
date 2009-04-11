/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <X11/Xlib.h>
#include "resolution/instance.hpp"
#include "../viewport_fun.hpp"
#include "../glx/current.hpp"
#include "../glx/context.hpp"
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/math/dim/basic_decl.hpp>
#include <sge/window/instance_fwd.hpp>
#include <sge/signal/connection_manager.hpp>
#include <sge/x11/window_fwd.hpp>
#include <sge/x11/visual_fwd.hpp>
#include <sge/x11/display_fwd.hpp>
#include <sge/scoped_ptr.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace renderer
{
struct parameters;
}

namespace ogl
{
namespace x11
{

class state {
	SGE_NONCOPYABLE(state)
public:
	state(
		renderer::parameters const &,
		renderer::adapter_type,
		window::instance_ptr,
		view_port_fun const &);
	
	void swap_buffers();
private:
	void reset_viewport_on_map(
		XEvent const &);
	void reset_viewport_on_configure(
		XEvent const &);

	view_port_fun              const set_viewport;
	renderer::screen_size      const screen_size_;
	sge::x11::window_ptr       const wnd;
	sge::x11::display_ptr      const display;
	sge::x11::const_visual_ptr const visual;
	glx::context_ptr           const context;
	glx::current               const current;
	scoped_ptr<
		resolution::instance
	> resolution_;
	signal::connection_manager con_manager;
};

}
}
}

#endif
