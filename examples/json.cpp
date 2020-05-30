//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/parse/json/find_member_exn.hpp>
#include <sge/parse/json/int_type.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/parse_string.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/output/to_stream.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>


int
main()
try
{
	return
		fcppt::either::match(
			sge::parse::json::parse_string(
				std::string{
					"{ \"foo\": 42, \"bar\" : { \"inner\" : 5.5, \"booltest\" : true } }"
				}
			),
			[](
				fcppt::parse::error<
					char
				> const &_error
			)
			{
				fcppt::io::cerr()
					<<
					fcppt::from_std_string(
						_error.get()
					)
					<<
					FCPPT_TEXT('\n');

				return
					EXIT_FAILURE;
			},
			[](
				sge::parse::json::start const &_result
			)
			{
				// assert that we have member foo
				sge::parse::json::find_member_exn<
					sge::parse::json::int_type
				>(
					fcppt::make_cref(
						_result.object().members
					),
					"foo"
				);

				// test if this also works with const results
				{
					sge::parse::json::object const &const_result(
						_result.object()
					);

					sge::parse::json::find_member_exn<
						sge::parse::json::int_type
					>(
						fcppt::make_cref(
							const_result.members
						),
						"foo"
					);
				}

				sge::parse::json::output::to_stream(
					std::cout,
					_result
				);

				fcppt::io::cout()
					<<
					FCPPT_TEXT('\n');

				return
					EXIT_SUCCESS;
			}
		);
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<<
		FCPPT_TEXT("caugth exception: ")
		<<
		_exception.string()
		<<
		FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
catch(
	std::exception const &_exception
)
{
	std::cout
		<<
		"caught exception: "
		<<
		_exception.what()
		<<
		'\n';

	return
		EXIT_FAILURE;
}
