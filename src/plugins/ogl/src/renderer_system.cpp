/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../renderer_system.hpp"
#include "../renderer.hpp"
#include "../xf86vidmode.hpp"

sge::renderer_ptr sge::ogl::renderer_system::create_renderer(const renderer_parameters& param, const int adapter, const window_ptr wnd)
{
	return renderer_ptr(new renderer(param, adapter, wnd));
}

void sge::ogl::renderer_system::caps(renderer_caps_array& v) const
{
	const x_display dsp;
	const int screen = DefaultScreen(dsp.get());
	const xf86_vidmode_array modes(dsp,screen);
	
	renderer_caps ret;
	for(xf86_vidmode_array::size_type i = 0; i < modes.size(); ++i)
		ret.display_modes.push_back(display_mode(modes[i].hdisplay, modes[i].vdisplay, BD_32, xf86_vidmode_array::refresh_rate(modes[i])));
	v.push_back(ret);
}
