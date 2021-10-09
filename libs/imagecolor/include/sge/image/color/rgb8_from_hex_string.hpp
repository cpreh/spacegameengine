//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_RGB8_FROM_HEX_STRING_HPP_INCLUDED
#define SGE_IMAGE_COLOR_RGB8_FROM_HEX_STRING_HPP_INCLUDED

#include <sge/image/color/rgb8.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/array/get.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/either/make_failure.hpp>
#include <fcppt/either/make_success.hpp>
#include <fcppt/either/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iomanip>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::image::color
{

// NOTES
// -----
//
// - I deliberately decided not to use fcppt::type_traits::is_string here to reduce compile time.
// - I wasn't sure if this function might be called for a string that
//   is not std::string or std::wstring (like a utf8 string), so I
//   kept this a template instead of two overloaded functions.
template <typename String>
fcppt::either::object<fcppt::string, sge::image::color::rgb8>
rgb8_from_hex_string(String const &_string)
{
  if (_string.length() != 6U)
  {
    return fcppt::either::make_failure<sge::image::color::rgb8>(
        fcppt::string{FCPPT_TEXT("Length is not 6")});
  }

  // Store the channels in unsigned instead of uint8_t because it
  // might be interpreted as a character instead of a number by the
  // iostreams
  using channel_array = fcppt::array::object<unsigned, 3U>;

  channel_array channels{fcppt::no_init{}};

  std::string::size_type current_position{0U};

  using stringstream_type =
      std::basic_istringstream<typename String::value_type, typename String::traits_type>;

  // Initialize the stringstream once for performance
  stringstream_type ss{};

  for (auto &channel : channels)
  {
    ss.clear();
    ss.str(_string.substr(current_position, 2U));
    // We cannot output the color string here without character
    // conversion, sorry.
    if (!(ss >> std::hex >> channel) || !ss.eof())
    {
      return fcppt::either::make_failure<sge::image::color::rgb8>(
          fcppt::string{FCPPT_TEXT("Invalid color component, cannot convert")});
    }

    current_position += 2U;
  }

  using channel_type = sge::image::color::rgb8::format::channel_type;

  return fcppt::either::make_success<fcppt::string>(sge::image::color::rgb8((
      sge::image::color::init::red() = static_cast<channel_type>(fcppt::array::get<0>(channels)))(
      sge::image::color::init::green() = static_cast<channel_type>(fcppt::array::get<1>(channels)))(
      sge::image::color::init::blue() =
          static_cast<channel_type>(fcppt::array::get<2>(channels)))));
}

}

#endif
