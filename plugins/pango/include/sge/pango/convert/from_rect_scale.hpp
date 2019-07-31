//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PANGO_CONVERT_FROM_RECT_SCALE_HPP_INCLUDED
#define SGE_PANGO_CONVERT_FROM_RECT_SCALE_HPP_INCLUDED

#include <sge/font/rect_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-types.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace pango
{
namespace convert
{

sge::font::rect
from_rect_scale(
	PangoRectangle const &
);

}
}
}

#endif
