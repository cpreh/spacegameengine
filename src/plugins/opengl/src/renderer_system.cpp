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


#include "../../../types.hpp"
#include "../../../exception.hpp"
#include "../renderer_system.hpp"
#include "../renderer.hpp"
#ifdef SGE_LINUX_PLATFORM
#include "../xf86vidmode.hpp"
#endif

sge::ogl::renderer_system::renderer_system()
: created(false)
{}

sge::renderer_ptr sge::ogl::renderer_system::create_renderer(const renderer_parameters& param, const int adapter, const window_ptr wnd)
{
	if(created)
		throw exception("The opengl plugin may only be used once for creating a renderer.");
	const renderer_ptr r(new renderer(param, adapter, wnd));
	created = true;
	return r;
}

const sge::renderer_caps_array sge::ogl::renderer_system::caps() const
{
	renderer_caps_array v;
#ifdef SGE_LINUX_PLATFORM
	const x_display_ptr dsp(new x_display());
	const int screen = DefaultScreen(dsp->get());
	const xf86_vidmode_array modes(dsp, screen);

	renderer_caps ret;
	for(xf86_vidmode_array::size_type i = 0; i < modes.size(); ++i)
		ret.display_modes.push_back(display_mode(modes[i].hdisplay, modes[i].vdisplay, bit_depth::depth32, xf86_vidmode_array::refresh_rate(modes[i])));
	v.push_back(ret);
#endif
	return v;
}
