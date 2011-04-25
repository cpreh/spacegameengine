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


#include <sge/projectile/body/parameters.hpp>

sge::projectile::body::parameters::parameters(
	sge::projectile::body::position const &_position,
	sge::projectile::body::linear_velocity const &_linear_velocity,
	sge::projectile::body::angular_velocity const &_angular_velocity,
	sge::projectile::shape::shared_base_ptr const &_shape,
	sge::projectile::body::rotation const &_rotation,
	sge::projectile::body::solidity::variant const &_solidity,
	sge::projectile::body::user_data const &_user_data)
:
	position_(
		_position),
	linear_velocity_(
		_linear_velocity),
	angular_velocity_(
		_angular_velocity),
	shape_(
		_shape),
	rotation_(
		_rotation),
	solidity_(
		_solidity),
	user_data_(
		_user_data)
{
}

sge::projectile::body::position const &
sge::projectile::body::parameters::position() const
{
	return position_;
}

sge::projectile::body::linear_velocity const &
sge::projectile::body::parameters::linear_velocity() const
{
	return linear_velocity_;
}

sge::projectile::body::angular_velocity const &
sge::projectile::body::parameters::angular_velocity() const
{
	return angular_velocity_;
}

sge::projectile::shape::shared_base_ptr const &
sge::projectile::body::parameters::shape() const
{
	return shape_;
}

sge::projectile::body::rotation const &
sge::projectile::body::parameters::rotation() const
{
	return rotation_;
}

sge::projectile::body::solidity::variant const &
sge::projectile::body::parameters::solidity() const
{
	return solidity_;
}

sge::projectile::body::user_data const &
sge::projectile::body::parameters::user_data() const
{
	return user_data_;
}
