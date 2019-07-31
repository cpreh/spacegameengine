//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opencl/exception.hpp>
#include <sge/opencl/program/file_to_source_string_sequence.hpp>
#include <sge/opencl/program/source_string_sequence.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::opencl::program::source_string_sequence
sge::opencl::program::file_to_source_string_sequence(
	boost::filesystem::path const &_path
)
{
	boost::filesystem::ifstream stream(
		_path
	);

	return
		sge::opencl::program::source_string_sequence{
			fcppt::optional::to_exception(
				fcppt::io::stream_to_string(
					stream
				),
				[
					&_path
				]{
					return
						sge::opencl::exception{
							FCPPT_TEXT("Failed to read ")
							+
							fcppt::filesystem::path_to_string(
								_path
							)
						};
				}
			)
		};
}
