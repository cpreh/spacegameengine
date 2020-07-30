//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PANGO_MAKE_METRICS_HPP_INCLUDED
#define SGE_PANGO_MAKE_METRICS_HPP_INCLUDED

#include <sge/font/metrics_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace pango
{

sge::font::metrics
make_metrics(
	PangoLayout & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}
}

#endif
