//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/config/exception.hpp>
#include <sge/config/getenv.hpp>
#include <sge/config/getenv_exn.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>


// TODO: Remove this

fcppt::string
sge::config::getenv_exn(
	fcppt::string const &_name
)
{
	return
		fcppt::optional::to_exception(
			sge::config::getenv(
				_name
			),
			[
				&_name
			]{
				return
					sge::config::exception(
						FCPPT_TEXT("Missing env var: ")
						+
						_name
					);
			}
		);
}
