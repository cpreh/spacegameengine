//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/unit.hpp>
#include <sge/pango/convert/to_unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-types.h>
#include <fcppt/config/external_end.hpp>

int sge::pango::convert::to_unit(sge::font::unit const _unit) { return _unit * PANGO_SCALE; }
