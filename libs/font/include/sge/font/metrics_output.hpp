//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_METRICS_OUTPUT_HPP_INCLUDED
#define SGE_FONT_METRICS_OUTPUT_HPP_INCLUDED

#include <sge/font/metrics_fwd.hpp>
#include <sge/font/detail/symbol.hpp>
#include <fcppt/io/ostream_fwd.hpp>


namespace sge::font
{

SGE_FONT_DETAIL_SYMBOL
fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &,
	sge::font::metrics const &
);

}

#endif
