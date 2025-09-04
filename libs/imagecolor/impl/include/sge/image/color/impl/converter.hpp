//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_CONVERTER_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_CONVERTER_HPP_INCLUDED

#include <sge/image/color/convert.hpp>
#include <sge/image/color/invalid_convert.hpp>
#include <sge/image/color/is_convertible.hpp>
#include <sge/image/color/tag.hpp>
#include <sge/image/color/impl/traits/format_map.hpp> // IWYU pragma: keep
#include <sge/image/impl/static_to_dynamic_format.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <mizuiro/color/object.hpp>
#include <mizuiro/color/format/argument.hpp>
#include <fcppt/not.hpp>

namespace sge::image::color::impl
{

struct converter
{
  template <typename DestFormat, typename Source>
  static sge::image::pixel::mizuiro_type<DestFormat> execute(
      Source const &_source,
      typename mizuiro::color::object<DestFormat>::format_store_type const & =
          mizuiro::color::format::argument<DestFormat>::get())
    requires(sge::image::color::is_convertible<typename Source::format, DestFormat>::value)
  {
    return sge::image::color::convert<DestFormat>(_source);
  }

  template <typename DestFormat, typename Source>
  [[noreturn]]
  static sge::image::pixel::mizuiro_type<DestFormat> execute(
      Source const &,
      typename mizuiro::color::object<DestFormat>::format_store_type const & =
          mizuiro::color::format::argument<DestFormat>::get())
    requires(
        fcppt::not_(sge::image::color::is_convertible<typename Source::format, DestFormat>::value))
  {
    throw sge::image::color::invalid_convert{
        sge::image::impl::
            static_to_dynamic_format<sge::image::color::tag, typename Source::format>::value,
        sge::image::impl::static_to_dynamic_format<sge::image::color::tag, DestFormat>::value};
  }
};

}

#endif
