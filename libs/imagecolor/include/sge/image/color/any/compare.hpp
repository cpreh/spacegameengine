//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_ANY_COMPARE_HPP_INCLUDED
#define SGE_IMAGE_COLOR_ANY_COMPARE_HPP_INCLUDED

#include <sge/image/color/any/object.hpp>
#include <mizuiro/color/compare.hpp>
#include <fcppt/variant/compare.hpp>

namespace sge::image::color::any
{

template <typename CompareChannels>
bool compare(
    sge::image::color::any::object const &_a,
    sge::image::color::any::object const &_b,
    CompareChannels const &_compare_channels)
{
  return fcppt::variant::compare(
      _a.get(),
      _b.get(),
      [&_compare_channels](auto const &_left, auto const &_right)
      { return mizuiro::color::compare(_left, _right, _compare_channels); });
}

}

#endif
