//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/exception.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/parameters_to_string.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/weight/unit.hpp>
#include <sge/gdifont/create_font.hpp>
#include <sge/gdifont/delete_object_deleter.hpp>
#include <sge/gdifont/hfont_unique_ptr.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe.hpp>

sge::gdifont::hfont_unique_ptr sge::gdifont::create_font(sge::font::parameters const &_parameters)
{
  HFONT const result(CreateFont(
      fcppt::optional::maybe(
          _parameters.ttf_size(),
          fcppt::const_(0),
          [](sge::font::ttf_size const _size) -> int
          {
            // TODO: convert this properly!
            return _size;
          }),
      0, // width
      0, // escapement
      0, // orientation
      fcppt::optional::maybe(
          _parameters.weight(),
          fcppt::const_(0),
          [](sge::font::weight::unit const _weight) { return fcppt::cast::to_signed(_weight); }),
      _parameters.italic() ? TRUE : FALSE,
      FALSE, // underline
      FALSE, // strikeout
      DEFAULT_CHARSET,
      OUT_DEFAULT_PRECIS,
      CLIP_DEFAULT_PRECIS,
      DEFAULT_QUALITY,
      DEFAULT_PITCH | FF_DONTCARE,
      fcppt::optional::from(_parameters.family(), [] { return fcppt::string(); }).c_str()));

  if (result == nullptr)
    throw sge::font::exception{
        FCPPT_TEXT("Unable to load GDI font: ") + sge::font::parameters_to_string(_parameters)};

  return sge::gdifont::hfont_unique_ptr(result);
}
