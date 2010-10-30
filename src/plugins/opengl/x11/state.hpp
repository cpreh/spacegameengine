/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "resolution/instance_fwd.hpp"
#include "../device_state.hpp"
#include "../viewport_fun.hpp"
#include "../glx/current.hpp"
#include "../glx/context_ptr.hpp"
#include <sge/renderer/adapter_type.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <awl/backends/x11/window_instance_ptr.hpp>
#include <awl/backends/x11/const_visual_ptr.hpp>
#include <awl/backends/x11/display_ptr.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

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
	)
public:
	state(
		renderer::parameters const &,
		renderer::adapter_type,
		awl::backends::x11::window_instance_ptr,
		opengl::viewport_fun const &
	);

	~state();

	void
	swap_buffers();
private:
	void
	reset_viewport_on_map(
		XEvent const &
	);

	void
	reset_viewport_on_configure(
		XEvent const &
	);

	opengl::viewport_fun const set_viewport_;

	renderer::screen_size const screen_size_;

	awl::backends::x11::window_instance_ptr const window_;

	awl::backends::x11::display_ptr const display_;

	awl::backends::x11::const_visual_ptr const visual_;

	glx::context_ptr const context_;

	glx::current const current_;

	fcppt::scoped_ptr<
		resolution::instance
	> resolution_;

	fcppt::signal::connection_manager const connection_manager_;
};

}
}
}

#endif
