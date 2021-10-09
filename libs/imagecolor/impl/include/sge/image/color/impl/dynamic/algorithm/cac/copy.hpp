//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_COPY_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_COPY_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/impl/dynamic/view/color_layout.hpp>
#include <sge/image/impl/algorithm/convert_may_overlap.hpp>
#include <sge/image/impl/algorithm/convert_uninitialized.hpp>
#include <mizuiro/image/algorithm/copy_different_channel_order.hpp>
#include <mizuiro/image/algorithm/copy_same_channel_order.hpp>
#include <mizuiro/image/algorithm/may_overlap.hpp>
#include <mizuiro/image/algorithm/uninitialized.hpp>

namespace sge::image::color::impl::dynamic::algorithm::cac
{

template <typename Source, typename Dest>
void copy(
    Source const &_source,
    Dest const &_dest,
    sge::image::algorithm::may_overlap const _overlap,
    sge::image::algorithm::uninitialized const _uninitialized)
{
  mizuiro::image::algorithm::may_overlap const mizuiro_overlap(
      sge::image::impl::algorithm::convert_may_overlap(_overlap));

  mizuiro::image::algorithm::uninitialized const mizuiro_uninitialized(
      sge::image::impl::algorithm::convert_uninitialized(_uninitialized));

  if (sge::image::color::impl::dynamic::view::color_layout(_source) ==
      sge::image::color::impl::dynamic::view::color_layout(_dest))
  {
    mizuiro::image::algorithm::copy_same_channel_order(
        _source, _dest, mizuiro_overlap, mizuiro_uninitialized);
  }
  else
  {
    mizuiro::image::algorithm::copy_different_channel_order(
        _source, _dest, mizuiro_overlap, mizuiro_uninitialized);
  }
}

}

#endif
