//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PANGO_CREATE_FONT_MAP_HPP_INCLUDED
#define SGE_PANGO_CREATE_FONT_MAP_HPP_INCLUDED

#include <sge/font/parameters_fwd.hpp>
#include <sge/pango/pango_font_map_unique_ptr.hpp>


namespace sge::pango
{

sge::pango::pango_font_map_unique_ptr
create_font_map(
	sge::font::parameters const &
);

}

#endif
