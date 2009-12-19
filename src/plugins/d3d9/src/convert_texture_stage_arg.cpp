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


#include "../convert_texture_stage_arg.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

D3DTEXTURESTAGESTATETYPE
sge::d3d9::convert_texture_stage_arg(
	renderer::texture_stage_arg::type const r)
{
	// TODO: maybe we have to swap numbers here
	switch(r) {
	case renderer::texture_stage_arg::rgb0:
		return D3DTSS_COLORARG0;
	case renderer::texture_stage_arg::rgb1:
		return D3DTSS_COLORARG1;
	case renderer::texture_stage_arg::rgb2:
		return D3DTSS_COLORARG2;
	case renderer::texture_stage_arg::alpha0:
		return D3DTSS_ALPHAARG0;
	case renderer::texture_stage_arg::alpha1:
		return D3DTSS_ALPHAARG1;
	case renderer::texture_stage_arg::alpha2:
		return D3DTSS_ALPHAARG2;
	default:
		throw exception(
			FCPPT_TEXT("Invalid texture_stage_arg!")
		);
	}
}
