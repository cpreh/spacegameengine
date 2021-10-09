//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_ALGORITHM_COPY_AND_CONVERT_STATIC_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_COPY_AND_CONVERT_STATIC_HPP_INCLUDED

#include <sge/image/mizuiro_color_traits.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/impl/algorithm/convert_may_overlap.hpp>
#include <sge/image/impl/algorithm/convert_uninitialized.hpp>
#include <sge/image/impl/traits/static_converter.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/view/object.hpp>
#include <mizuiro/image/algorithm/copy_and_convert.hpp>
#include <fcppt/variant/apply.hpp>

namespace sge
{
namespace image
{
namespace impl
{
namespace algorithm
{

template <typename Tag>
void copy_and_convert_static(
    sge::image::view::const_object<Tag> const &_src,
    sge::image::view::object<Tag> const &_dest,
    sge::image::algorithm::may_overlap const _overlap,
    sge::image::algorithm::uninitialized const _uninitialized)
{
  fcppt::variant::apply(
      [_overlap, _uninitialized](auto const &_src_inner, auto const &_dest_inner)
      {
        return mizuiro::image::algorithm::copy_and_convert<
            sge::image::impl::traits::static_converter<sge::image::traits::image::color_tag<Tag>>>(
            _src_inner,
            _dest_inner,
            sge::image::impl::algorithm::convert_may_overlap(_overlap),
            sge::image::impl::algorithm::convert_uninitialized(_uninitialized));
      },
      _src.get(),
      _dest.get());
}

}
}
}
}

#endif
