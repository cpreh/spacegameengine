#include <sge/opencl/program/file_to_source_string_sequence.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/io/stream_to_string.hpp>


sge::opencl::program::source_string_sequence const
sge::opencl::program::file_to_source_string_sequence(
	fcppt::filesystem::path const &f)
{
	return
		fcppt::assign::make_container<sge::opencl::program::source_string_sequence>(
			fcppt::io::stream_to_string(
				*fcppt::make_unique_ptr<fcppt::io::cifstream>(
					f)));
}
