//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/parameters.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/weight/unit.hpp>
#include <sge/pango/create_layout.hpp>
#include <sge/pango/font_description.hpp>
#include <sge/pango/glib_deleter.hpp>
#include <sge/pango/pango_layout_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <pango/pango-types.h>
#include <fcppt/config/external_end.hpp>

sge::pango::pango_layout_unique_ptr sge::pango::create_layout(
    fcppt::reference<PangoContext> const _context, sge::font::parameters const &_parameters)
{
  sge::pango::font_description font_description{};

  fcppt::optional::maybe_void(
      _parameters.ttf_size(),
      [&font_description](sge::font::ttf_size const _ttf_size)
      { font_description.ttf_size(_ttf_size * PANGO_SCALE); });

  fcppt::optional::maybe_void(
      _parameters.family(),
      [&font_description](fcppt::string const &_family) { font_description.family(_family); });

  fcppt::optional::maybe_void(
      _parameters.weight(),
      [&font_description](sge::font::weight::unit const _weight)
      { font_description.weight(_weight); });

  if (_parameters.italic())
  {
    font_description.italic();
  }

  sge::pango::pango_layout_unique_ptr result(::pango_layout_new(&_context.get()));

  ::pango_layout_set_font_description(result.get_pointer(), font_description.get());

  return result;
}
