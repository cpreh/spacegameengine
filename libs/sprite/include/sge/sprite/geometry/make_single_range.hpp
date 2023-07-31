//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_GEOMETRY_MAKE_SINGLE_RANGE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_MAKE_SINGLE_RANGE_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/geometry/random_access_range_impl.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

namespace sge::sprite::geometry
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

template <typename Choices>
sge::sprite::geometry::random_access_range<sge::sprite::object<Choices> *>
make_single_range(sge::sprite::object<Choices> &_object)
{
  return sge::sprite::geometry::random_access_range<sge::sprite::object<Choices> *>(
      &_object,
      &_object + 1 // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  );
}

template <typename Choices>
sge::sprite::geometry::random_access_range<sge::sprite::object<Choices> const *>
make_single_range(sge::sprite::object<Choices> const &_object)
{
  return sge::sprite::geometry::random_access_range<sge::sprite::object<Choices> const *>(
      &_object,
      &_object + 1 // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  );
}

FCPPT_PP_POP_WARNING

}

#endif
