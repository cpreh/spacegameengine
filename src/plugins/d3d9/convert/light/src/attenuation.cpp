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


#include "../attenuation.hpp"
#include <sge/renderer/light/attenuation.hpp>

void
sge::d3d9::convert::light::attenuation(
	D3DLIGHT9 &_light,
	renderer::light::attenuation const &_attenuation
)
{
	_light.Attenuation0
		= _attenuation.constant_attenuation().get();

	_light.Attenuation1
		= _attenuation.linear_attenuation().get();

	_light.Attenuation2
		= _attenuation.quadratic_attenuation().get();
}
