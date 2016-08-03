/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/projectile/body/solidity/nonsolid.hpp>
#include <sge/projectile/body/solidity/solid.hpp>
#include <sge/projectile/body/solidity/static.hpp>
#include <sge/projectile/body/solidity/variant.hpp>
#include <sge/projectile/impl/body/solidity/extract_mass.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <LinearMath/btScalar.h>
#include <fcppt/config/external_end.hpp>


btScalar
sge::projectile::impl::body::solidity::extract_mass(
	sge::projectile::body::solidity::variant const &_solidity
)
{
	return
		fcppt::variant::match(
			_solidity,
			[](
				sge::projectile::body::solidity::static_ const &
			)
			{
				return
					fcppt::literal<
						btScalar
					>(
						0
					);
			},
			[](
				sge::projectile::body::solidity::solid const &_solid
			)
			{
				return
					_solid.mass().get();
			},
			[](
				sge::projectile::body::solidity::nonsolid const &
			)
			{
				return
					fcppt::literal<
						btScalar
					>(
						1
					);
			}
		);
}
