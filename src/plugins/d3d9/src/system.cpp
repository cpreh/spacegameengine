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
#include <sge/renderer/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>

sge::d3d9::renderer_system::renderer_system()
:
	sys_(
		::Direct3DCreate9(
			D3D_SDK_VERSION
		)
	)
{
	if(
		!sys_
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Initialization of d3d failed!")
		);
}

sge::renderer::device_ptr const
sge::d3d9::system::create_renderer(
	renderer::parameters const &_param,
	renderer::adapter const _adapter,
	sge::window::instance_ptr const _window
)
{
	return
		fcppt::make_shared_ptr<
			d3d9::device
		>(
			sys_,
			_param,
			_adapter,
			_window
		);
}

sge::window::instance_ptr const
sge::d3d9::system::create_window(
	awl::system::object_ptr const _awl_system,
	sge::window::simple_parameters const &_window_params,
	sge::renderer::parameters const &_render_params
)
{
#if 0
	return sge::windows::create_window(
		wparam,
		rparam
	);
#endif
}
