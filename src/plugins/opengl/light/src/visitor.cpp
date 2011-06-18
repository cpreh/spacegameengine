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


#include "../visitor.hpp"
#include "../directional.hpp"
#include "../point.hpp"
#include "../spot.hpp"

sge::opengl::light::visitor::visitor(
	light::index const _index
)
:
	index_(_index)
{
}

sge::opengl::light::visitor::result_type
sge::opengl::light::visitor::operator()(
	sge::renderer::light::directional const &_directional
) const
{
	light::directional(
		index_,
		_directional
	);
}

sge::opengl::light::visitor::result_type
sge::opengl::light::visitor::operator()(
	sge::renderer::light::point const &_point
) const
{
	light::point(
		index_,
		_point
	);
}

sge::opengl::light::visitor::result_type
sge::opengl::light::visitor::operator()(
	sge::renderer::light::spot const &_spot
) const
{
	light::spot(
		index_,
		_spot
	);
}
