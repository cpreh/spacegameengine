//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/to_fcppt_string.hpp>
#include <sge/cegui/to_wstring.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/String.h>
#include <fcppt/config/external_end.hpp>


fcppt::optional_string
sge::cegui::to_fcppt_string(
	CEGUI::String const &_string
)
{
	return
		fcppt::from_std_wstring(
			sge::cegui::to_wstring(
				_string
			)
		);
}
