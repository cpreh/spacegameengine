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


#include <sge/opengl/light/attenuation.hpp>
#include <sge/opengl/light/cutoff_angle.hpp>
#include <sge/opengl/light/direction.hpp>
#include <sge/opengl/light/position.hpp>
#include <sge/opengl/light/spot.hpp>
#include <sge/renderer/light/spot.hpp>


void
sge::opengl::light::spot(
	light::index const _index,
	renderer::light::spot const &_spot
)
{
	light::position(
		_index,
		_spot.position()
	);

	light::direction(
		_index,
		_spot.direction()
	);

	light::cutoff_angle(
		_index,
		_spot.cutoff_angle()
	);

	light::attenuation(
		_index,
		_spot.attenuation()
	);
}
