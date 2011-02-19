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


#include "../system.hpp"
#include "../device.hpp"
#include "../convert/bit_depth.hpp"
#include "../convert/depth_buffer.hpp"
#include "../convert/stencil_buffer.hpp"
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/window/to_awl_parameters.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <awl/system/object.hpp>
#include <awl/window/parameters.hpp>

sge::opengl::system::system()
{
}

sge::opengl::system::~system()
{
}

sge::renderer::device_ptr const
sge::opengl::system::create_renderer(
	renderer::parameters const &_param,
	renderer::adapter_type const _adapter,
	window::instance_ptr const _wnd
)
{
	return
		fcppt::make_shared_ptr<
			device
		>(
			_param,
			_adapter,
			_wnd
		);
}

awl::window::instance_ptr const
sge::opengl::system::create_window(
	awl::system::object_ptr const _system,
	sge::window::simple_parameters const &_wparam,
	sge::renderer::parameters const &_rparam
)
{
	return
		_system->create(
			sge::window::to_awl_parameters(
				_wparam
			)
			.has_opengl(
				true
			)
			.bit_depth(
				opengl::convert::bit_depth(
					_rparam.display_mode()
					?
						_rparam.display_mode()->bit_depth()
					:
						sge::renderer::bit_depth::depth32
				)
			)
			.stencil_buffer(
				opengl::convert::stencil_buffer(
					_rparam.stencil_buffer()
				)
			)
			.depth_buffer(
				opengl::convert::depth_buffer(
					_rparam.depth_buffer()
				)
			)
		);
}
