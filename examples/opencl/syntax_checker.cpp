/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/log/default_level.hpp>
#include <sge/log/default_level_streams.hpp>
#include <sge/opencl/log_location.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <sge/opencl/program/build_error.hpp>
#include <sge/opencl/program/build_parameters.hpp>
#include <sge/opencl/program/object.hpp>
#include <sge/opencl/program/optional_build_parameters.hpp>
#include <sge/opencl/single_device_system/object.hpp>
#include <sge/opencl/single_device_system/parameters.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/main.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/config/compiler.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/filesystem/open_exn.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/optional_level.hpp>
#include <fcppt/options/apply.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/default_help_switch.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp>
#include <fcppt/options/help_text.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/make_many.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse_help.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

int
main_program(
	boost::filesystem::path const &_target_file_name,
	std::vector<
		fcppt::string
	> const &_additional_args
)
{
	fcppt::log::context log_context(
		sge::log::default_level(),
		sge::log::default_level_streams()
	);

	log_context.set(
		sge::opencl::log_location(),
		fcppt::log::optional_level{
			fcppt::log::level::verbose
		}
	);

	sge::opencl::single_device_system::object opencl_system{
		log_context,
		sge::opencl::single_device_system::parameters()
	};

	std::ifstream stream(
		fcppt::filesystem::open_exn<
			std::ifstream
		>(
			_target_file_name,
			std::ios_base::in
		)
	);

	sge::opencl::program::object main_program(
		log_context,
		opencl_system.context(),
		sge::opencl::program::source_string_sequence{
			fcppt::io::stream_to_string(
				stream
			)
		},
		sge::opencl::program::optional_build_parameters()
	);

	try
	{
		fcppt::io::cout()
			<<
			FCPPT_TEXT("Compiling ")
			<<
			fcppt::filesystem::path_to_string(
				_target_file_name
			)
			<<
			FCPPT_TEXT("...")
			<<
			std::endl;

		main_program.build(
			sge::opencl::program::build_parameters()
				.options(
					fcppt::algorithm::fold(
						_additional_args,
						std::string{},
						[](
							fcppt::string const &_arg,
							std::string &&_state
						)
						{
							return
								std::move(
									_state
								)
								+=
								" "
								+
								fcppt::to_std_string(
									_arg
								);
						}
					)
				)
		);

		fcppt::io::cout()
			<<
			FCPPT_TEXT("Done, 0 errors!\n");
	}
	catch(
		sge::opencl::program::build_error const &_error
	)
	{
		typedef
		std::vector<
			fcppt::string
		>
		line_sequence;

		line_sequence lines;

		boost::algorithm::split(
			lines,
			_error.message(),
			boost::is_any_of(
				FCPPT_TEXT("\n")
			)
		);

FCPPT_PP_PUSH_WARNING
#if defined(FCPPT_CONFIG_GNU_GCC_COMPILER)
FCPPT_PP_DISABLE_GCC_WARNING(-Wzero-as-null-pointer-constant)
#endif

		boost::xpressive::basic_regex<
			fcppt::string::const_iterator
		> const broken_error_indicator_regex{
			boost::xpressive::bos >>
			FCPPT_TEXT(':') >>
			+boost::xpressive::_d >>
			FCPPT_TEXT(':') >>
			+boost::xpressive::_d >>
			FCPPT_TEXT(':')
		};

		boost::xpressive::basic_regex<
			fcppt::string::const_iterator
		> const builtin_error_string{
			boost::xpressive::bos >>
			FCPPT_TEXT("<built-in>:") >>
			+boost::xpressive::_d >>
			FCPPT_TEXT(':') >>
			+boost::xpressive::_d >>
			FCPPT_TEXT(':')
		};


		for(
			fcppt::string const &line
			:
			lines
		)
		{
			boost::xpressive::match_results<
				fcppt::string::const_iterator
			> what;

			if(
				boost::xpressive::regex_search(
					line,
					what,
					broken_error_indicator_regex
				)
			)
			{
				fcppt::io::cerr()
					<<
					fcppt::filesystem::path_to_string(
						_target_file_name
					)
					<<
					line
					<<
					FCPPT_TEXT('\n');
			}
			else if(
				boost::xpressive::regex_search(
					line,
					what,
					builtin_error_string
				)
			)
			{
				fcppt::io::cerr()
					<<
					boost::xpressive::regex_replace(
						line,
						builtin_error_string,
						FCPPT_TEXT("<built-in>:")
					)
					<<
					FCPPT_TEXT('\n');
			}
			else
			{
				fcppt::io::cerr()
					<<
					line
					<<
					FCPPT_TEXT('\n');
			}
		}
FCPPT_PP_POP_WARNING

		return
			EXIT_FAILURE;
	}

	opencl_system.update();

	return
		EXIT_SUCCESS;
}

FCPPT_RECORD_MAKE_LABEL(
	argument_label
);

FCPPT_RECORD_MAKE_LABEL(
	path_label
);

}

int
FCPPT_MAIN(
	int argc,
	fcppt::args_char *argv[]
)
try
{
	auto const parser(
		fcppt::options::apply(
			fcppt::options::argument<
				path_label,
				fcppt::string
			>{
				fcppt::options::long_name{
					FCPPT_TEXT("cl-file")
				},
				fcppt::options::optional_help_text{
					fcppt::options::help_text{
						FCPPT_TEXT("path to the opencl file")
					}
				}
			},
			fcppt::options::make_many(
				fcppt::options::argument<
					argument_label,
					fcppt::string
				>{
					fcppt::options::long_name{
						FCPPT_TEXT("additional-argument")
					},
					fcppt::options::optional_help_text{
						fcppt::options::help_text{
							FCPPT_TEXT("additional argument to the opencl program")
						}
					}
				}
			)
		)
	);

	typedef
	fcppt::options::result_of<
		decltype(
			parser
		)
	>
	result_type;

	auto const handle_options(
		[](
			fcppt::options::result<
				result_type
			> const &_result
		)
		{
			return
				fcppt::either::match(
					_result,
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
						fcppt::options::result_of<
							decltype(
								parser
							)
						> const &_value
					)
					{
						return
							main_program(
								fcppt::record::get<
									path_label
								>(
									_value
								),
								fcppt::record::get<
									argument_label
								>(
									_value
								)
							);
					}
				);
		}
	);

	return
		fcppt::variant::match(
			fcppt::options::parse_help(
				fcppt::options::default_help_switch(),
				parser,
				fcppt::args_from_second(
					argc,
					argv
				)
			),
			[
				&handle_options
			](
				fcppt::options::result<
					result_type
				> const &_result
			)
			{
				return
					handle_options(
						_result
					);
			},
			[](
				fcppt::options::help_text const &_help_text
			)
			{
				fcppt::io::cout()
					<<
					FCPPT_TEXT("This program loads and builds a program. It outputs the syntax errors encountered.\n\n")
					<<
					_help_text
					<<
					FCPPT_TEXT('\n');

				return
					EXIT_SUCCESS;
			}
		);
}
catch(
	fcppt::exception const &_error
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
catch(
	std::exception const &_error
)
{
	std::cerr
		<<
		_error.what()
		<<
		'\n';

	return
		EXIT_FAILURE;
}
