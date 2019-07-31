//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/parse/json/detail/to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/from.hpp>


fcppt::string
sge::parse::json::detail::to_fcppt_string(
	sge::charconv::utf8_string const &_string
)
{
	return
		fcppt::optional::from(
			sge::charconv::utf8_string_to_fcppt(
				_string
			),
			[]{
				return
					fcppt::string{
						FCPPT_TEXT("Conversion error")
					};
			}
		);
}
