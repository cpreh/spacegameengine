//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_BODY_SOLIDITY_VARIANT_FWD_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_SOLIDITY_VARIANT_FWD_HPP_INCLUDED

#include <sge/projectile/body/solidity/nonsolid_fwd.hpp>
#include <sge/projectile/body/solidity/solid_fwd.hpp>
#include <sge/projectile/body/solidity/static_fwd.hpp>
#include <fcppt/variant/variadic_fwd.hpp>


namespace sge
{
namespace projectile
{
namespace body
{
namespace solidity
{

typedef
fcppt::variant::variadic<
	sge::projectile::body::solidity::static_,
	sge::projectile::body::solidity::solid,
	sge::projectile::body::solidity::nonsolid
>
variant;

}
}
}
}

#endif
