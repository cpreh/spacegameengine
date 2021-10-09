//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_ALGORITHM_COMPARE_VISITOR_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_COMPARE_VISITOR_HPP_INCLUDED

#include <sge/image/impl/algorithm/compare_element.hpp>
#include <mizuiro/color/make_compare_function.hpp>
#include <mizuiro/image/algorithm/compare.hpp>

namespace sge::image::impl::algorithm
{

struct compare_visitor
{
  template <typename View1, typename View2>
  bool operator()(View1 const &, View2 const &) const
  {
    return false;
  }

  template <typename View>
  bool operator()(View const &_view1, View const &_view2) const
  {
    return mizuiro::image::algorithm::compare(
        _view1,
        _view2,
        mizuiro::color::make_compare_function(sge::image::algorithm::compare_element()));
  }
};

}

#endif
