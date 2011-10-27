#ifndef SGE_OPENCL_PROGRAM_FILE_TO_SOURCE_STRING_SEQUENCE_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_FILE_TO_SOURCE_STRING_SEQUENCE_HPP_INCLUDED

#include <sge/opencl/symbol.hpp>
#include <sge/opencl/program/source_string_sequence.hpp>
#include <fcppt/filesystem/path.hpp>


namespace sge
{
namespace opencl
{
namespace program
{
SGE_OPENCL_SYMBOL program::source_string_sequence const
file_to_source_string_sequence(
	fcppt::filesystem::path const &);
}
}
}

#endif
