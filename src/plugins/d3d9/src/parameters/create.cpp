/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/parameters/create.hpp>
#include <sge/d3d9/parameters/extract_size.hpp>
#include <sge/d3d9/parameters/convert/bit_depth.hpp>
#include <sge/d3d9/parameters/convert/depth_stencil_buffer.hpp>
#include <sge/d3d9/parameters/convert/multi_sample.hpp>
#include <sge/d3d9/parameters/convert/multi_sample_quality.hpp>
#include <sge/renderer/parameters/object.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <awl/window/object.hpp>


D3DPRESENT_PARAMETERS const
sge::d3d9::parameters::create(
	sge::renderer::parameters::object const &_parameters,
	awl::window::object &_window
)
{
	sge::renderer::screen_size const back_buffer_size(
		sge::d3d9::parameters::extract_size(
			_parameters.display_mode(),
			_window
		)
	);

	bool const has_depth_stencil(
		_parameters.pixel_format().depth_stencil()
		!=
		sge::renderer::pixel_format::depth_stencil::off
	);

	bool const is_windowed(
		!_parameters.display_mode()
	);

	D3DPRESENT_PARAMETERS const ret =
	{
		back_buffer_size.w(), // BackBufferWidth
		back_buffer_size.h(), // BackBufferHeight
		sge::d3d9::parameters::convert::bit_depth(
			_parameters.pixel_format().color()
		), // BackBufferFormat
		1u, // BackBufferCount,
		sge::d3d9::parameters::convert::multi_sample(
			_parameters.pixel_format().multi_samples()
		),
		sge::d3d9::parameters::convert::multi_sample_quality(
			_parameters.pixel_format().multi_samples()
		),
		D3DSWAPEFFECT_DISCARD, // SwapEffect
		dynamic_cast<
			awl::backends::windows::window::object &
		>(
			_window
		).hwnd(), // hDeviceWindow
		is_windowed, // Windowed
		has_depth_stencil, // EnableAutoDepthStencil
		sge::d3d9::parameters::convert::depth_stencil_buffer(
			_parameters.pixel_format().depth_stencil()
		), // AutoDepthStencilFormat
		has_depth_stencil
		?
			D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL
		:
			0u, // Flags
		// FullScreen_RefreshRateInHz
		(
			!is_windowed && _parameters.display_mode()->refresh_rate()
		)
		?
			_parameters.display_mode()->refresh_rate()->get()
		:
			0u
		,
		_parameters.vsync() == sge::renderer::parameters::vsync::on
		?
			D3DPRESENT_INTERVAL_ONE
		:
			D3DPRESENT_INTERVAL_IMMEDIATE // PresentationInterval
	};

	return ret;
}
