//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_CONVERT_VISITOR_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_CONVERT_VISITOR_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp> // IWYU pragma: keep

namespace sge::image::color::impl::dynamic::algorithm::cac
{

template <typename Function>
class convert_visitor
{
public:
  explicit convert_visitor(Function const &_function) : function_(_function) {}

  using result_type = void;

  template <typename Src, typename Dest>
  result_type operator()(Src const &_src, Dest const &_dest) const
  {
    _dest = function_(_src, _dest.format_store());
  }

private:
  Function function_;
};

}

#endif
