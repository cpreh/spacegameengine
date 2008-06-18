/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/sprite/animation_series.hpp>

sge::sprite::animation_series::animation_series()
{}

sge::sprite::animation_series::animation_series(
	entity_vector const& entities)
: entities(entities)
{}

void sge::sprite::animation_series::push_back(
	animation_entity const& entity)
{
	entities.push_back(entity);
}

sge::sprite::animation_series::const_iterator
sge::sprite::animation_series::begin() const
{
	return entities.begin();
}

sge::sprite::animation_series::const_iterator
sge::sprite::animation_series::end() const
{
	return entities.end();
}

bool sge::sprite::animation_series::empty() const
{
	return entities.empty();
}
	
const sge::renderer::texture::dim_type
sge::sprite::animation_series::dim() const
{
	return entities.at(0).dim();
}
