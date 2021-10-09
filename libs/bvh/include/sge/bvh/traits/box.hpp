//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_BVH_TRAITS_BOX_HPP_INCLUDED
#define SGE_BVH_TRAITS_BOX_HPP_INCLUDED

#include <fcppt/math/size_type.hpp>
#include <fcppt/math/box/object.hpp>

namespace sge::bvh::traits
{
template <typename Box>
struct box
{
};

template <typename T, fcppt::math::size_type N>
struct box<fcppt::math::box::object<T, N>>
{
  using type = fcppt::math::box::object<T, N>;

  static type extract_box(type const &b) { return b; }
};
}

#endif
