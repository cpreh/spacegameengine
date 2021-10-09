//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PANGO_GET_STRONG_CURSOR_POS_HPP_INCLUDED
#define SGE_PANGO_GET_STRONG_CURSOR_POS_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>

namespace sge::pango
{

PangoRectangle get_strong_cursor_pos(
    PangoLayout &, // NOLINT(google-runtime-references)
    int);

}

#endif
