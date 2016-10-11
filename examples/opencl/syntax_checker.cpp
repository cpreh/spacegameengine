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
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/config/compiler.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/optional_level.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>


int
main(
	int argc,
	char *argv[]
)
try
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

	// TODO: Use args
	if(argc < 2)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("This program loads and builds a program. It outputs the syntax errors encountered.\n\n")
			<< FCPPT_TEXT("Usage: ")
			<< fcppt::from_std_string(argv[0])
			<< FCPPT_TEXT(" <cl-file-name> <additional-parameters>\n");
		return EXIT_FAILURE;
	}

	boost::filesystem::path const target_file_name(
		fcppt::from_std_string(
			argv[1]));

	std::string additional_parameters;
	for(int i = 2; i < argc; ++i)
		additional_parameters += " "+std::string(argv[i]);

	// Mind the extra parens
	sge::opencl::single_device_system::object opencl_system(
		log_context,
		sge::opencl::single_device_system::parameters()
	);

	boost::filesystem::ifstream stream(
		target_file_name
	);

	sge::opencl::program::object main_program(
		log_context,
		opencl_system.context(),
		sge::opencl::program::source_string_sequence{
			fcppt::io::stream_to_string(
				stream
			)
		},
		sge::opencl::program::optional_build_parameters());

	try
	{
		fcppt::io::cout() << FCPPT_TEXT("Compiling ") << fcppt::filesystem::path_to_string(target_file_name) << FCPPT_TEXT("...") << std::endl;
		main_program.build(
			sge::opencl::program::build_parameters()
				.options(
					additional_parameters));
		fcppt::io::cout() << FCPPT_TEXT("Done, 0 errors!\n");
	}
	catch(sge::opencl::program::build_error const &e)
	{
		typedef
		std::vector<fcppt::string>
		line_sequence;

		line_sequence lines;
		boost::algorithm::split(
			lines,
			e.message(),
			boost::is_any_of(FCPPT_TEXT("\n")));

FCPPT_PP_PUSH_WARNING
#if defined(FCPPT_CONFIG_GNU_GCC_COMPILER)
FCPPT_PP_DISABLE_GCC_WARNING(-Wzero-as-null-pointer-constant)
#endif

		boost::xpressive::basic_regex<fcppt::string::const_iterator> broken_error_indicator_regex =
			boost::xpressive::bos >>
			FCPPT_TEXT(':') >>
			+boost::xpressive::_d >>
			FCPPT_TEXT(':') >>
			+boost::xpressive::_d >>
			FCPPT_TEXT(':');

		boost::xpressive::basic_regex<fcppt::string::const_iterator> builtin_error_string =
			boost::xpressive::bos >>
			FCPPT_TEXT("<built-in>:") >>
			+boost::xpressive::_d >>
			FCPPT_TEXT(':') >>
			+boost::xpressive::_d >>
			FCPPT_TEXT(':');


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
						target_file_name
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
}
catch(
	fcppt::exception const &_error)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
