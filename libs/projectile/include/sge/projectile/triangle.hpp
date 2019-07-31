//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_TRIANGLE_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGLE_HPP_INCLUDED

#include <sge/projectile/vector2.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace projectile
{
typedef
std::array
<
	sge::projectile::vector2,
	3
>
triangle;
}
}

#endif
