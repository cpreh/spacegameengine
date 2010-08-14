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


#include "../convert_multi_sample.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

D3DMULTISAMPLE_TYPE
sge::d3d9::convert_multi_sample(
	renderer::multi_sample_type const r)
{
	switch(r) {
	case 0:
	case 1:
		return D3DMULTISAMPLE_NONE;
	case 2:
		return D3DMULTISAMPLE_2_SAMPLES;
	case 3:
		return D3DMULTISAMPLE_3_SAMPLES;
	case 4:
		return D3DMULTISAMPLE_4_SAMPLES;
	case 5:
		return D3DMULTISAMPLE_5_SAMPLES;
	case 6:
		return D3DMULTISAMPLE_6_SAMPLES;
	case 7:
		return D3DMULTISAMPLE_7_SAMPLES;
	case 8:
		return D3DMULTISAMPLE_8_SAMPLES;
	case 9:
		return D3DMULTISAMPLE_9_SAMPLES;
	case 10:
		return D3DMULTISAMPLE_10_SAMPLES;
	case 11:
		return D3DMULTISAMPLE_11_SAMPLES;
	case 12:
		return D3DMULTISAMPLE_12_SAMPLES;
	case 13:
		return D3DMULTISAMPLE_13_SAMPLES;
	case 14:
		return D3DMULTISAMPLE_14_SAMPLES;
	case 15:
		return D3DMULTISAMPLE_15_SAMPLES;
	case 16:
		return D3DMULTISAMPLE_16_SAMPLES;
	default:
		throw exception(
			FCPPT_TEXT("Invalid multi_sample_type value (must be <= 16)!")
		);
	}
}
