/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../convert_texture_stage_arg_value.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

DWORD
sge::d3d9::convert_texture_stage_arg_value(
	renderer::texture_stage_arg_value::type const r)
{
	switch(r) {
	case renderer::texture_stage_arg_value::constant:
		return D3DTA_CONSTANT;
	case renderer::texture_stage_arg_value::current:
		return D3DTA_CURRENT;
//		return D3DTA_DIFFUSE;
//		return D3DTA_SPECULAR;
//		return D3DTA_TEMP;
	case renderer::texture_stage_arg_value::texture:
		return D3DTA_TEXTURE;
	default:
		throw exception(
			FCPPT_TEXT("Invalid texture_stage_arg_value!")
		);
	}
}
