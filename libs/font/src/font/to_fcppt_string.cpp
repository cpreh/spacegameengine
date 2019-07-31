//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/string.hpp>
#include <sge/font/to_fcppt_string.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <fcppt/optional_string.hpp>


fcppt::optional_string
sge::font::to_fcppt_string(
	sge::font::string const &_string
)
{
	return
		fcppt::from_std_wstring(
			_string
		);
}
