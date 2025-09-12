//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_PERMUTATE_COMPARE_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_PERMUTATE_COMPARE_HPP_INCLUDED

#include <fcppt/algorithm/all_of.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

namespace sge::image::color::impl::dynamic::algorithm::cac
{

template <typename Layout>
bool permutate_compare(Layout const &_layout1, Layout const &_layout2)
{
  return fcppt::algorithm::all_of(
      _layout1,
      [&_layout2](auto const &_elem) { return std::ranges::contains(_layout2, _elem); });
}

}

#endif
