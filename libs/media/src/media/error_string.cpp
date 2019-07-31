//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/media/error_string.hpp>
#include <sge/media/name.hpp>
#include <sge/media/optional_name.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe.hpp>


fcppt::string
sge::media::error_string(
	sge::media::optional_name const &_opt_name,
	fcppt::string const &_message
)
{
	return
		fcppt::optional::maybe(
			_opt_name,
			[
				&_message
			]
			{
				return
					FCPPT_TEXT("stream: ")
					+
					_message;
			},
			[
				&_message
			](
				sge::media::name const &_name
			)
			{
				return
					FCPPT_TEXT("\"")
					+
					_name.get()
					+
					FCPPT_TEXT("\": ")
					+
					_message;
			}
		);
}
