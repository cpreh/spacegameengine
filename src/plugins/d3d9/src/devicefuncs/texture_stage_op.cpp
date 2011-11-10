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


#include <sge/d3d9/convert/texture_stage_op.hpp>
#include <sge/d3d9/convert/texture_stage_op_value.hpp>
#include <sge/d3d9/devicefuncs/texture_stage_op.hpp>
#include <sge/d3d9/devicefuncs/set_texture_stage_state.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <sge/renderer/texture/stage_op.hpp>
#include <sge/renderer/texture/stage_op_value.hpp>

void
sge::d3d9::devicefuncs::texture_stage_op(
	IDirect3DDevice9 *const _device,
	renderer::texture::stage const _stage,
	renderer::texture::stage_op::type const _op,
	renderer::texture::stage_op_value::type const _value
)
{
	devicefuncs::set_texture_stage_state(
		_device,
		_stage,
		d3d9::convert::texture_stage_op(
			_op
		),
		d3d9::convert::texture_stage_op_value(
			_value
		)
	);
}
