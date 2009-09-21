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


#include "../present_parameters.hpp"
#include "../convert_multi_sample.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <tr1/array>
#include <boost/foreach.hpp>

namespace
{

D3DFORMAT
search_format(
	sge::renderer::display_mode const &mode,
	d3d_ptr const sys)
{
	switch(mode.depth()) {
	case sge::renderer::bit_depth::d16:
		return D3DFMT_R5G6B5;
	case sge::renderer::bit_depth::d32:
		return D3DFMT_X8R8G8B8;
	default:
		throw sge::exception(
			SGE_TEXT("You may only pass valid bit_depths!")
		);
	}
}

bool check_stencil_match(
	sge::renderer::adapter_type const adapter,
	D3DFORMAT const screen_format,
	D3DFORMAT const to_test,
	sge::d3d9::d3d_ptr const sys)
{
	return sys->CheckDepthStencilMatch(
		adapter,
		D3DDEVTYPE_HAL,
		screen_format,
		screen_format,
		to_test
	) == D3D_OK;
}

D3DFORMAT
search_stencil_format(
	sge::renderer::adapter_type const adapter,
	D3DFORMAT const screen_format,
	sge::d3d9::d3d_ptr const sys)
{
	typedef std::tr1::array<
		D3DFORMAT,
		2
	> array_type;

	array_type const array = {{
		D3DFMT_D24S8,
		D3DFMT_D16
	}};

	BOOST_FOREACH(
		array_type::const_reference fmt,
		array
	)
		if(
			check_stencil_match(
				adapter,
				screen_format,
				D3DFMT_D24S8,
				fmt
			)
		)
			return fmt;

	return D3DFMT_UNKNOWN;
}

}

D3DPRESENT_PARAMETERS const
sge::d3d9::create_present_parameters(
	renderer::parameters const &param,
	renderer::adapter_type const adapter,
	windows::window_ptr const wnd,
	d3d_ptr const sys)
{
	D3DFORMAT const format(
		search_format(
			param.mode(),
			sys
		)
	);

	D3DPRESENT_PARAMETERS pp;
	pp.AutoDepthStencilFormat = search_stencil_format(adapter,format,sys);
	pp.BackBufferCount = 1;
	pp.BackBufferFormat = format;
	pp.BackBufferHeight = param.mode().height();
	pp.BackBufferWidth = param.mode().width();
	pp.EnableAutoDepthStencil = TRUE;
	pp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCI;
	pp.FullScreen_RefreshRateInHz = param.wmode() == renderer::window_mode::windowed ? 0 : param.mode().refresh_rate();
	pp.hDeviceWindow = wnd->hwnd();
	pp.MultiSampleQuality = 0;
	pp.MultiSampleType = convert_multi_sample(param.samples());
	pp.PresentationInterval = param.vsync ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.Windowed = param.windowed;

	return pp;
}
