//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/metrics.hpp>
#include <sge/font/metrics_output.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/ostream.hpp>


fcppt::io::ostream &
sge::font::operator<<(
	fcppt::io::ostream &_stream,
	sge::font::metrics const &_metrics
)
{
	return
		_stream
		<<
		FCPPT_TEXT("( height: ")
		<<
		_metrics.height()
		<<
		FCPPT_TEXT(')');
}
