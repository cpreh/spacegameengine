//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PANGO_PANGO_FONT_MAP_UNIQUE_PTR_HPP_INCLUDED
#define SGE_PANGO_PANGO_FONT_MAP_UNIQUE_PTR_HPP_INCLUDED

#include <sge/pango/glib_deleter.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-types.h>
#include <fcppt/config/external_end.hpp>

namespace sge::pango
{

using pango_font_map_unique_ptr = fcppt::unique_ptr<PangoFontMap, sge::pango::glib_deleter>;

}

#endif
