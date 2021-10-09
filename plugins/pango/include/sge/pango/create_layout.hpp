//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PANGO_CREATE_LAYOUT_HPP_INCLUDED
#define SGE_PANGO_CREATE_LAYOUT_HPP_INCLUDED

#include <sge/font/parameters_fwd.hpp>
#include <sge/pango/pango_layout_unique_ptr.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-types.h>
#include <fcppt/config/external_end.hpp>

namespace sge::pango
{

sge::pango::pango_layout_unique_ptr
create_layout(fcppt::reference<PangoContext>, sge::font::parameters const &);

}

#endif
