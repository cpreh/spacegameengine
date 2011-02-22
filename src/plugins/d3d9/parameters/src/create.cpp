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


#include "../present_parameters.hpp"
#include "../convert_multi_sample.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/tr1/array.hpp>
#include <boost/foreach.hpp>

namespace
{

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
sge::d3d9::parameters::create(
	d3d9::d3d_ptr const _system,
	renderer::parameters const &_param,
	renderer::adapter_type const _adapter,
	awl::backends::windows::window::instance_ptr const _window
)
{
	D3DFORMAT const back_buffer_format(
		parameters::extract_back_buffer_format(
			_param.screen_mode()
		)
	);

	sge::renderer::screen_size const back_buffer_size(
		parameters::extract_size(
			_param.screen_mode(),
			_window
		)
	);

	bool const is_windowed(
		fcppt::variant::holds_type<
			sge::renderer::visual_depth::type
		>(
			_param.screen_mode()
		)
	);

	D3DPRESENT_PARAMETERS const ret =
	{
		back_buffer_size.w(), // BackBufferWidth
		back_buffer_size.h(), // BackBufferHeight 
		back_buffer_format, // BackBufferFormat
		1u, // BackBufferCount,
		convert::multi_sample_type(
			_param.multi_samples()
		),
		0u, // MultiSampleQuality TODO?
		D3DSWAPEFFECT_DISCARD, // SwapEffect
		_window->hwnd(), // hDeviceWindow 
		is_windowed, // Windowed
		_param.depth_stencil_buffer() != sge::renderer::depth_stencil_buffer::off // EnableAutoDepthStencil
		params::depth_stencil_format(
			_system,
			_adapter,
			_param.depth_stencil_buffer()
		), // AutoDepthStencilFormat
		D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL, // Flags
		is_windowed
		?
			0
		:
			_param.screen_mode().get<
				sge::renderer::display_mode
			>().refresh_rate(), // FullScreen_RefreshRateInHz
		_param.vsync() == sge::renderer::vsync::on
		?
			D3DPRESENT_INTERVAL_ONE
		:
			D3DPRESENT_INTERVAL_IMMEDIATE // PresentationInterval
	};

	return ret;
}
