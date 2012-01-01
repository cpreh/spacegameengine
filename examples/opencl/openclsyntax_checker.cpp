/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/exception.hpp>
#include <sge/log/global_context.hpp>
#include <sge/opencl/kernel/object.hpp>
#include <sge/opencl/program/build_error.hpp>
#include <sge/opencl/program/build_parameters.hpp>
#include <sge/opencl/program/object.hpp>
#include <sge/opencl/program/optional_build_parameters.hpp>
#include <sge/opencl/single_device_system/object.hpp>
#include <sge/opencl/single_device_system/parameters.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/log/deactivate_levels.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>


int
main(
	int argc,
	char *argv[])
try
{
	sge::log::global_context().apply(
		fcppt::log::location(
			FCPPT_TEXT("opencl")),
		std::tr1::bind(
			&fcppt::log::deactivate_levels,
			std::tr1::placeholders::_1,
			fcppt::log::level::verbose));

	if(argc != 2)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("This program loads and builds a program. It outputs the syntax errors encountered.\n\n")
			<< FCPPT_TEXT("Usage: ")
			<< fcppt::from_std_string(argv[0])
			<< FCPPT_TEXT(" <cl-file-name>\n");
		return EXIT_FAILURE;
	}

	fcppt::filesystem::path const target_file_name(
		fcppt::from_std_string(
			argv[1]));

	// Mind the extra parens
	sge::opencl::single_device_system::object opencl_system(
		(sge::opencl::single_device_system::parameters()));

	sge::opencl::program::object main_program(
		opencl_system.context(),
		fcppt::assign::make_container<sge::opencl::program::source_string_sequence>(
			fcppt::io::stream_to_string(
				*fcppt::make_unique_ptr<fcppt::io::cifstream>(
					target_file_name))),
		sge::opencl::program::optional_build_parameters());

	try
	{
		main_program.build(
			sge::opencl::program::build_parameters());
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

		for(line_sequence::const_iterator it = lines.begin(); it != lines.end(); ++it)
		{
			boost::xpressive::match_results<fcppt::string::const_iterator> what;
			if(boost::xpressive::regex_search(*it,what,broken_error_indicator_regex))
			{
				fcppt::io::cerr() << fcppt::filesystem::path_to_string(target_file_name) << *it << FCPPT_TEXT("\n");
			}
			else if(boost::xpressive::regex_search(*it,what,builtin_error_string))
			{
				fcppt::io::cerr()
					<<
						boost::xpressive::regex_replace(
							*it,
							builtin_error_string,
							FCPPT_TEXT("<built-in>:"))
					<< FCPPT_TEXT("\n");
			}
			else
			{
				fcppt::io::cerr() << *it << FCPPT_TEXT("\n");
			}
		}
		return EXIT_FAILURE;
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
