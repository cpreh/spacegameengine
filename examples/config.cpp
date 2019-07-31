//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/config/app_name.hpp>
#include <sge/config/config_path.hpp>
#include <sge/config/user_name.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <fcppt/config/external_end.hpp>


int main()
try
{
	fcppt::io::cout()
		<< FCPPT_TEXT("Config path: ")
		<< sge::config::config_path(
			sge::config::app_name(
				FCPPT_TEXT("sgeconfigtest")
			)
		)
		<< FCPPT_TEXT('\n');

	fcppt::io::cout()
		<< FCPPT_TEXT("User name: ")
		<< sge::config::user_name()
		<< FCPPT_TEXT('\n');
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
