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


#include <sge/sprite/animation/series.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sge::sprite::animation::series::series()
{}

sge::sprite::animation::series::series(
	entity_vector const &_entities
)
:
	entities_(
		_entities
	)
{}

void
sge::sprite::animation::series::push_back(
	entity const &entity_
)
{
	entities_.push_back(
		entity_
	);
}

sge::sprite::animation::entity_vector &
sge::sprite::animation::series::entities()
{
	return entities_;
}

sge::sprite::animation::entity_vector const &
sge::sprite::animation::series::entities() const
{
	return entities_;
}

sge::sprite::animation::series::const_iterator
sge::sprite::animation::series::begin() const
{
	return entities_.begin();
}

sge::sprite::animation::series::const_iterator
sge::sprite::animation::series::end() const
{
	return entities_.end();
}

bool
sge::sprite::animation::series::empty() const
{
	return entities_.empty();
}
