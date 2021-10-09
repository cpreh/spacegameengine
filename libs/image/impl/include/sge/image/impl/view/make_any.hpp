//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_VIEW_MAKE_ANY_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_MAKE_ANY_HPP_INCLUDED

#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/dim.hpp>
#include <sge/image/pitch.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image/impl/to_mizuiro_dim.hpp>
#include <sge/image/impl/view/object_from_constness.hpp>
#include <sge/image/impl/view/to_static_format.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/pixel/format_fwd.hpp>
#include <sge/image/view/mizuiro_type.hpp>
#include <mizuiro/choose_const.hpp>
#include <fcppt/use.hpp>
#include <fcppt/enum/to_static.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::image::impl::view
{

template <typename Tag, typename Constness>
sge::image::impl::view::object_from_constness<Tag, Constness> make_any(
    mizuiro::choose_const<Constness, sge::image::raw_pointer, sge::image::const_raw_pointer> const
        _data,
    sge::image::dim<Tag> const &_dim,
    sge::image::traits::pixel::format<sge::image::traits::image::color_tag<Tag>> const _format,
    sge::image::pitch<Tag> const &_pitch)
{
  return fcppt::enum_::to_static<
      sge::image::traits::pixel::format<sge::image::traits::image::color_tag<Tag>>>(
      _format,
      [&_dim, &_pitch, _data](auto const &_static_format)
      {
        FCPPT_USE(_static_format);

        using view_type = sge::image::view::mizuiro_type<
            sge::image::impl::view::to_static_format<Tag, std::decay_t<decltype(_static_format)>>,
            Constness>;

        return sge::image::impl::view::object_from_constness<Tag, Constness>{view_type{
            sge::image::impl::to_mizuiro_dim(_dim),
            _data,
            sge::image::impl::to_mizuiro_dim(_pitch)}};
      });
}

}

#endif
