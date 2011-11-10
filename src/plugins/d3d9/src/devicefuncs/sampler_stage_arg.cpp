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


#include <sge/d3d9/convert/sampler_stage_arg.hpp>
#include <sge/d3d9/convert/sampler_stage_arg_value.hpp>
#include <sge/d3d9/devicefuncs/sampler_stage_arg.hpp>
#include <sge/d3d9/devicefuncs/set_texture_stage_state.hpp>


void
sge::d3d9::devicefuncs::sampler_stage_arg(
	IDirect3DDevice9 *const _device,
	renderer::texture::stage const _stage,
	renderer::sampler_stage_arg::type const _arg,
	renderer::sampler_stage_arg_value::type const _value
)
{
	devicefuncs::set_texture_stage_state(
		_device,
		_stage,
		d3d9::convert::sampler_stage_arg(
			_arg
		),
		d3d9::convert::sampler_stage_arg_value(
			_value
		)
	);
}
