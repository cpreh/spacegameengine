//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PANGO_CREATE_TEXT_LAYOUT_HPP_INCLUDED
#define SGE_PANGO_CREATE_TEXT_LAYOUT_HPP_INCLUDED

#include <sge/charconv/utf8_string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/pango/pango_layout_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>

namespace sge::pango
{

sge::pango::pango_layout_unique_ptr create_text_layout(
    PangoLayout &, // NOLINT(google-runtime-references)
    sge::charconv::utf8_string const &,
    sge::font::text_parameters const &);

}

#endif
