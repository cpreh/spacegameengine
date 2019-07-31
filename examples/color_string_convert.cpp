//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/exception.hpp>
#include <sge/image/color/any/from_string.hpp>
#include <sge/image/color/any/print.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/main.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wmissing-declarations)

int
FCPPT_MAIN(
	int argc,
	fcppt::args_char **argv
)
try
{
	FCPPT_RECORD_MAKE_LABEL(
		string_label
	);

	typedef
	fcppt::options::argument<
		string_label,
		fcppt::string
	>
	argument;

	typedef
	fcppt::options::result_of<
		argument
	>
	result_type;

	argument const parser{
		fcppt::options::long_name{
			FCPPT_TEXT("color-string")
		},
		fcppt::options::optional_help_text{}
	};

	return
		fcppt::either::match(
			fcppt::options::parse(
				parser,
				fcppt::args_from_second(
					argc,
					argv
				)
			),
			[](
				fcppt::options::error const &_error
			)
			{
				fcppt::io::cerr()
					<<
					_error
					<<
					FCPPT_TEXT('\n');

				return
					EXIT_FAILURE;
			},
			[](
				result_type const &_result
			)
			{
				fcppt::io::cout()
					<<
					sge::image::color::any::from_string(
						fcppt::record::get<
							string_label
						>(
							_result
						)
					)
					<<
					FCPPT_TEXT('\n');

				return
					EXIT_SUCCESS;
			}
		);
}
catch(
	 sge::image::exception const &_error
)
{
	 fcppt::io::cerr()
	 	<<
		_error.string()
		<<
		FCPPT_TEXT('\n');

	 return
	 	EXIT_FAILURE;
}

FCPPT_PP_POP_WARNING
