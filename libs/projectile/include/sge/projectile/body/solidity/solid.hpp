//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_BODY_SOLIDITY_SOLID_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_SOLIDITY_SOLID_HPP_INCLUDED

#include <sge/projectile/body/mass.hpp>
#include <sge/projectile/body/solidity/solid_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>


namespace sge::projectile::body::solidity
{

class solid
{
public:
	SGE_PROJECTILE_DETAIL_SYMBOL
	explicit
	solid(
		sge::projectile::body::mass const &
	);

	[[nodiscard]]
	SGE_PROJECTILE_DETAIL_SYMBOL
	sge::projectile::body::mass const &
	mass() const;
private:
	sge::projectile::body::mass mass_;
};

}

#endif
