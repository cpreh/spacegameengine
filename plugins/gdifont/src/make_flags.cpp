//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/text_parameters.hpp>
#include <sge/gdifont/format.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/make_flags.hpp>
#include <sge/gdifont/convert/align_h.hpp>
#include <sge/gdifont/convert/flags.hpp>


sge::gdifont::format const
sge::gdifont::make_flags(
	sge::font::text_parameters const &_parameters
)
{
	return
		sge::gdifont::format(
			sge::gdifont::convert::flags(
				_parameters.flags()
			)
			|
			sge::gdifont::convert::align_h(
				_parameters.align_h()
			)
		);
}
