//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_CHOOSE_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_CHOOSE_HPP_INCLUDED

#include <sge/image/color/invalid_convert.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/function.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/rgb_to_srgb.hpp>
#include <sge/image/color/impl/dynamic/algorithm/cac/srgb_to_rgb.hpp>
#include <sge/image/color/impl/dynamic/view/color_format.hpp>
#include <mizuiro/color/conversion/rgb_to_srgb.hpp>
#include <mizuiro/color/conversion/same_to_same.hpp>
#include <mizuiro/color/conversion/srgb_to_rgb.hpp>
#include <mizuiro/color/format/same_spaces.hpp>
#include <fcppt/not.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::image::color::impl::dynamic::algorithm::cac
{

template <typename SourceFormat, typename DestFormat>
inline std::enable_if_t<
    mizuiro::color::format::
        same_spaces<typename SourceFormat::color_format, typename DestFormat::color_format>::value,
    sge::image::color::impl::dynamic::algorithm::cac::function<SourceFormat, DestFormat>>
choose(SourceFormat const &, DestFormat const &)
{
  return &mizuiro::color::conversion::same_to_same<
      typename DestFormat::color_format,
      sge::image::color::impl::dynamic::algorithm::cac::source<SourceFormat>>;
}

template <typename SourceFormat, typename DestFormat>
inline std::enable_if_t<
    sge::image::color::impl::dynamic::algorithm::cac::rgb_to_srgb<SourceFormat, DestFormat>::value,
    sge::image::color::impl::dynamic::algorithm::cac::function<SourceFormat, DestFormat>>
choose(SourceFormat const &, DestFormat const &)
{
  return &mizuiro::color::conversion::rgb_to_srgb<
      typename DestFormat::color_format,
      sge::image::color::impl::dynamic::algorithm::cac::source<SourceFormat>>;
}

template <typename SourceFormat, typename DestFormat>
inline std::enable_if_t<
    sge::image::color::impl::dynamic::algorithm::cac::srgb_to_rgb<SourceFormat, DestFormat>::value,
    sge::image::color::impl::dynamic::algorithm::cac::function<SourceFormat, DestFormat>>
choose(SourceFormat const &, DestFormat const &)
{
  return &mizuiro::color::conversion::srgb_to_rgb<
      typename DestFormat::color_format,
      sge::image::color::impl::dynamic::algorithm::cac::source<SourceFormat>>;
}

template <typename SourceFormat, typename DestFormat>
inline std::enable_if_t<
    fcppt::not_(
        mizuiro::color::format::same_spaces<
            typename SourceFormat::color_format,
            typename DestFormat::color_format>::value ||
        sge::image::color::impl::dynamic::algorithm::cac::rgb_to_srgb<SourceFormat, DestFormat>::
            value ||
        sge::image::color::impl::dynamic::algorithm::cac::srgb_to_rgb<SourceFormat, DestFormat>::
            value),
    sge::image::color::impl::dynamic::algorithm::cac::function<SourceFormat, DestFormat>>
choose(SourceFormat const &_source, DestFormat const &_dest)
{
  throw sge::image::color::invalid_convert{
      sge::image::color::impl::dynamic::view::color_format(_source).color_format,
      sge::image::color::impl::dynamic::view::color_format(_dest).color_format};
}

}

#endif
