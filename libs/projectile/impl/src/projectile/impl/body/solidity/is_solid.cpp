//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/body/solidity/nonsolid.hpp>
#include <sge/projectile/body/solidity/variant.hpp>
#include <sge/projectile/impl/body/solidity/is_solid.hpp>
#include <fcppt/variant/holds_type.hpp>


bool
sge::projectile::impl::body::solidity::is_solid(
	sge::projectile::body::solidity::variant const &_variant
)
{
	return
		!fcppt::variant::holds_type<
			sge::projectile::body::solidity::nonsolid
		>(
			_variant
		);
}
