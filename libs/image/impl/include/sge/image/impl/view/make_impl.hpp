//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_MAKE_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_MAKE_IMPL_HPP_INCLUDED

#include <sge/image/dim.hpp>
#include <sge/image/pitch.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image/impl/view/make_any.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/object.hpp>
#include <mizuiro/nonconst_tag.hpp>

template <typename Tag>
sge::image::view::object<Tag> sge::image::view::make(
    sge::image::raw_pointer const _data, // NOLINT(readability-non-const-parameter)
    sge::image::dim<Tag> const &_dim,
    sge::image::traits::pixel::format<sge::image::traits::image::color_tag<Tag>> const _format,
    sge::image::pitch<Tag> const &_pitch)
{
  return sge::image::impl::view::make_any<Tag, mizuiro::nonconst_tag>(_data, _dim, _format, _pitch);
}

#endif
