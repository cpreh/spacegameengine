//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_RGBA8_FROM_HEX_STRING_HPP_INCLUDED
#define SGE_IMAGE_COLOR_RGBA8_FROM_HEX_STRING_HPP_INCLUDED

#include <sge/image/color/rgb8.hpp>
#include <sge/image/color/rgb8_from_hex_string.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <mizuiro/color/channel/blue.hpp>
#include <mizuiro/color/channel/green.hpp>
#include <mizuiro/color/channel/red.hpp>
#include <fcppt/string.hpp>
#include <fcppt/either/map.hpp>
#include <fcppt/either/object_impl.hpp>

namespace sge::image::color
{

template <typename String>
fcppt::either::object<fcppt::string, sge::image::color::rgba8> rgba8_from_hex_string(
    String const &_string, sge::image::color::rgba8::format::channel_type const _alpha)
{
  return fcppt::either::map(
      sge::image::color::rgb8_from_hex_string(_string),
      [_alpha](sge::image::color::rgb8 const _rgb)
      {
        return sge::image::color::rgba8(
            (sge::image::color::init::red() = _rgb.get(mizuiro::color::channel::red()))(
                sge::image::color::init::green() = _rgb.get(mizuiro::color::channel::green()))(
                sge::image::color::init::blue() = _rgb.get(mizuiro::color::channel::blue()))(
                sge::image::color::init::alpha() = _alpha));
      });
}

}

#endif
