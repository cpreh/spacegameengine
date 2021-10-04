//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PANGO_XY_TO_INDEX_HPP_INCLUDED
#define SGE_PANGO_XY_TO_INDEX_HPP_INCLUDED

#include <sge/font/vector_fwd.hpp>
#include <sge/pango/optional_index.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


namespace sge::pango
{

sge::pango::optional_index
xy_to_index(
	PangoLayout &, // NOLINT(google-runtime-references)
	sge::font::vector const &
);

}

#endif
