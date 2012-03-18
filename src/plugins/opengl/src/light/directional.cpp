/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/vector4f.hpp>
#include <sge/opengl/light/cutoff_angle.hpp>
#include <sge/opengl/light/direction.hpp>
#include <sge/opengl/light/directional.hpp>
#include <sge/opengl/light/position_impl.hpp>
#include <sge/renderer/light/directional.hpp>
#include <fcppt/math/vector/object_impl.hpp>


void
sge::opengl::light::directional(
	light::index const _index,
	renderer::light::directional const &_directional
)
{
	light::direction(
		_index,
		_directional.direction()
	);

	light::cutoff_angle(
		_index,
		_directional.cutoff_angle()
	);

	// special value to make this a directional light
	light::position_impl(
		_index,
		opengl::vector4f::null()
	);
}
