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


#include "../create.hpp"
#include "../extract_back_buffer_format.hpp"
#include "../extract_size.hpp"
#include "../convert/depth_stencil_buffer.hpp"
#include "../convert/multi_sample.hpp"
#include "../convert/multi_sample_quality.hpp"
#include "../../d3dinclude.hpp"
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/visual_depth.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/window/instance.hpp>
#include <awl/backends/windows/window/instance.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>

D3DPRESENT_PARAMETERS const
sge::d3d9::parameters::create(
	renderer::parameters const &_param,
	sge::window::instance  &_window
)
{
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
		parameters::extract_back_buffer_format(
			_param.screen_mode()
		), // BackBufferFormat
		1u, // BackBufferCount,
		parameters::convert::multi_sample(
			_param.samples()
		),
		parameters::convert::multi_sample_quality(
			_param.samples()
		),
		D3DSWAPEFFECT_DISCARD, // SwapEffect
		fcppt::dynamic_pointer_cast<
			awl::backends::windows::window::instance
		>(
			_window.awl_instance()
		)->hwnd(), // hDeviceWindow 
		is_windowed, // Windowed
		_param.depth_stencil_buffer() != sge::renderer::depth_stencil_buffer::off, // EnableAutoDepthStencil
		parameters::convert::depth_stencil_buffer(
			_param.depth_stencil_buffer()
		), // AutoDepthStencilFormat
		_param.depth_stencil_buffer() != sge::renderer::depth_stencil_buffer::off
		?
			D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL
		:
			0, // Flags
		is_windowed
		?
			0u
		:
			_param.screen_mode().get<
				sge::renderer::display_mode
			>().refresh_rate().get(), // FullScreen_RefreshRateInHz
		_param.vsync() == sge::renderer::vsync::on
		?
			D3DPRESENT_INTERVAL_ONE
		:
			D3DPRESENT_INTERVAL_IMMEDIATE // PresentationInterval
	};

	return ret;
}
