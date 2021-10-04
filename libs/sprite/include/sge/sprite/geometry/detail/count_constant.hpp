//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_COUNT_CONSTANT_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_COUNT_CONSTANT_HPP_INCLUDED

#include <sge/sprite/geometry/detail/count.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::sprite::geometry::detail
{

template<
	sge::sprite::geometry::detail::count Count
>
using count_constant
=
std::integral_constant<
	sge::sprite::geometry::detail::count,
	Count
>;

}

#endif
