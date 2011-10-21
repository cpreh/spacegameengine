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


#ifndef SGE_PROJECTILE_BODY_PARAMETERS_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_PARAMETERS_HPP_INCLUDED

#include <sge/projectile/symbol.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/angular_velocity.hpp>
#include <sge/projectile/body/linear_velocity.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <sge/projectile/body/user_data.hpp>
#include <sge/projectile/body/solidity/variant.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/math/vector/basic_impl.hpp>


namespace sge
{
namespace projectile
{
namespace body
{
class parameters
{
FCPPT_NONASSIGNABLE(
	parameters);
public:
	SGE_PROJECTILE_SYMBOL explicit
	parameters(
		sge::projectile::body::position const &,
		sge::projectile::body::linear_velocity const &,
		sge::projectile::body::angular_velocity const &,
		sge::projectile::shape::shared_base_ptr const &,
		sge::projectile::body::rotation const &,
		sge::projectile::body::solidity::variant const &,
		sge::projectile::body::user_data const &);

	SGE_PROJECTILE_SYMBOL sge::projectile::body::position const &
	position() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::body::linear_velocity const &
	linear_velocity() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::body::angular_velocity const &
	angular_velocity() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::shape::shared_base_ptr const &
	shape() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::body::rotation const &
	rotation() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::body::solidity::variant const &
	solidity() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::body::user_data const &
	user_data() const;
private:
	sge::projectile::body::position position_;
	sge::projectile::body::linear_velocity linear_velocity_;
	sge::projectile::body::angular_velocity angular_velocity_;
	sge::projectile::shape::shared_base_ptr shape_;
	sge::projectile::body::rotation rotation_;
	sge::projectile::body::solidity::variant solidity_;
	sge::projectile::body::user_data user_data_;
};
}
}
}

#endif
