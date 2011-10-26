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


#include <sge/d3d9/convert/sampler_stage_op_value.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <fcppt/assert/unreachable.hpp>

DWORD
sge::d3d9::convert::sampler_stage_op_value(
	renderer::sampler_stage_op_value::type const _value
)
{
	switch(
		_value
	)
	{
	//	return D3DTOP_DISABLE;
	//	return D3DTOP_SELECTARG2;
	case renderer::sampler_stage_op_value::arg0:
		return D3DTOP_SELECTARG1; // TODO: maybe we have to use a different arg number here
	case renderer::sampler_stage_op_value::modulate:
		return D3DTOP_MODULATE;
	/*
	case renderer::sampler_stage_op_value::modulate2x:
		return D3DTOP_MODULATE2X;
	case renderer::sampler_stage_op_value::modulate4x:
		return D3DTOP_MODULATE4X;*/
	case renderer::sampler_stage_op_value::add:
		return D3DTOP_ADD;
	case renderer::sampler_stage_op_value::add_signed:
		return D3DTOP_ADDSIGNED;
	//case renderer::sampler_stage_op_value::add_signed2x:
		//return D3DTOP_ADDSIGNED2X;
	case renderer::sampler_stage_op_value::substract:
		return D3DTOP_SUBTRACT;
	//	return D3DTOP_ADDSMOOTH;
	//	return D3DTOP_BLENDDIFFUSEALPHA;
//		return D3DTOP_BLENDTEXTUREALPHA;
//		return D3DTOP_BLENDFACTORALPHA;
//		return D3DTOP_BLENDTEXTUREALPHAPM;
//		return D3DTOP_BLENDCURRENTALPHA;
//		return D3DTOP_PREMODULATE;
//		return D3DTOP_MODULATEALPHA_ADDCOLOR;
//		return D3DTOP_MODULATECOLOR_ADDALPHA;
//		return D3DTOP_MODULATEINVALPHA_ADDCOLOR;
//		return D3DTOP_MODULATEINVCOLOR_ADDALPHA;
//		return D3DTOP_BUMPENVMAP;
//		return D3DTOP_BUMPENVMAPLUMINANCE;
//		return D3DTOP_DOTPRODUCT3;
//		return D3DTOP_MULTIPLYADD;
//		return D3DTOP_LERP;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
