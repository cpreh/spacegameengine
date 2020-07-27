//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_SHAPE_DETAIL_SCALAR_CONTAINER_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_DETAIL_SCALAR_CONTAINER_HPP_INCLUDED

#include <sge/projectile/scalar.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace projectile
{
namespace shape
{
namespace detail
{

using
scalar_container
=
std::vector<
	sge::projectile::scalar
>;

}
}
}
}

#endif
