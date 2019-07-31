//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_IS_RANDOM_ACCESS_RANGE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_IS_RANDOM_ACCESS_RANGE_HPP_INCLUDED

#include <sge/sprite/geometry/random_access_range_fwd.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{

template<
	typename T
>
struct is_random_access_range
:
std::false_type
{
};

template<
	typename Iterator
>
struct is_random_access_range<
	sge::sprite::geometry::random_access_range<
		Iterator
	>
>
:
std::true_type
{
};

}
}
}

#endif
