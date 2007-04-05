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


#include "../../../ptr_cast.hpp"
#include "../../../renderer/types.hpp"
#include "../../../win32_window.hpp"
#include "../enumeration.hpp"
#include "../constants.hpp"
#include "../conversion.hpp"

#include <iostream>
#include <algorithm>

void sge::d3d::create_renderer_caps(const unsigned adapter, const d3d_ptr sys, renderer_caps& c)
{
	D3DCAPS9 caps;
	if(sys->GetDeviceCaps(adapter,D3DDEVTYPE_HAL,&caps) != D3D_OK)
		throw std::runtime_error("GetDeviceCaps failed");

	D3DADAPTER_IDENTIFIER9 identifier;
	if(sys->GetAdapterIdentifier(adapter,0,&identifier) != D3D_OK)
		throw std::runtime_error("GetAdapterIdentifier failed");

	c.adapter_number = adapter;
	c.max_tex_size = caps.MaxTextureWidth;
	if(caps.MaxTextureWidth != caps.MaxTextureHeight)
		std::cerr << "Warning: MaxTextureWidth != MaxTextureHeight (case not handled)\n";
	c.max_tex_height = std::min(caps.MaxTextureHeight, caps.MaxTextureWidth);
	c.driver_name = &identifier.Driver[0];
	c.description = &identifier.Description[0];

	add_display_modes(c.display_modes, adapter, BD_16, D3DFMT_A1R5G5B5, sys);
	add_display_modes(c.display_modes, adapter, BD_16, D3DFMT_X1R5G5B5, sys);
	add_display_modes(c.display_modes, adapter, BD_16, D3DFMT_R5G6B5,   sys);
	add_display_modes(c.display_modes, adapter, BD_32, D3DFMT_A8R8G8B8, sys);
	add_display_modes(c.display_modes, adapter, BD_32, D3DFMT_X8R8G8B8, sys);
}

void sge::d3d::add_display_modes(display_mode_array& v, const unsigned adapter, const bit_depth depth, const D3DFORMAT format, const d3d_ptr sys)
{
	const unsigned modes = sys->GetAdapterModeCount(adapter,format);
	for(unsigned i = 0; i < modes; ++i)
	{
		D3DDISPLAYMODE mode;
		sys->EnumAdapterModes(adapter,format,i,&mode);
		if(mode.Width >= 640 && mode.Height >= 480)
			v.push_back(display_mode(mode.Width,mode.Height,depth,mode.RefreshRate));
	}
}

D3DFORMAT sge::d3d::search_format(const display_mode& mode, const d3d_ptr sys)
{
	switch(mode.depth) {
	case BD_16:
		return D3DFMT_R5G6B5;
	case BD_32:
		return D3DFMT_X8R8G8B8;
	default:
		throw std::logic_error("You may only pass valid bit_depths");
	}
}

DWORD sge::d3d::get_tnl_caps(const unsigned adapter, const d3d_ptr sys)
{
	DWORD r = 0;
	D3DCAPS9 caps;
	sys->GetDeviceCaps(adapter,D3DDEVTYPE_HAL,&caps);
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		r |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
		if(caps.DevCaps & D3DDEVCAPS_PUREDEVICE)
			r |= D3DCREATE_PUREDEVICE;
	}
	else
		r |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	return r;
}

D3DFORMAT sge::d3d::search_stencil_format(const unsigned adapter, const D3DFORMAT screen_format, const d3d_ptr sys)
{
	if(sys->CheckDepthStencilMatch(adapter,D3DDEVTYPE_HAL,screen_format,screen_format,D3DFMT_D24S8) == D3D_OK)
		return D3DFMT_D24S8;
	if(sys->CheckDepthStencilMatch(adapter,D3DDEVTYPE_HAL,screen_format,screen_format,D3DFMT_D16) == D3D_OK)
		return D3DFMT_D16;
	return D3DFMT_UNKNOWN;
}

D3DPRESENT_PARAMETERS sge::d3d::create_present_parameters(const renderer_parameters& param, const int adapter, const win32_window_ptr wnd, const d3d_ptr sys)
{
	const D3DFORMAT format = search_format(param.mode,sys);

	D3DPRESENT_PARAMETERS pp;
	pp.AutoDepthStencilFormat = search_stencil_format(adapter,format,sys);
	pp.BackBufferCount = constants::back_buffer_count;
	pp.BackBufferFormat = format;
	pp.BackBufferHeight = param.mode.height();
	pp.BackBufferWidth = param.mode.width();
	pp.EnableAutoDepthStencil = constants::enable_auto_depth_stencil;
	pp.Flags = constants::flags;
	pp.FullScreen_RefreshRateInHz = param.windowed ? 0 : param.mode.refresh_rate;
	pp.hDeviceWindow = wnd->hwnd();
	pp.MultiSampleQuality = 0;
	pp.MultiSampleType = convert_cast<D3DMULTISAMPLE_TYPE>(param.samples);
	pp.PresentationInterval = param.vsync ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
	pp.SwapEffect = constants::swap_effect();
	pp.Windowed = param.windowed;

	return pp;
}
