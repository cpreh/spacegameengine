//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_PROGRAM_FILE_TO_SOURCE_STRING_SEQUENCE_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_FILE_TO_SOURCE_STRING_SEQUENCE_HPP_INCLUDED

#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/program/source_string_sequence.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opencl
{
namespace program
{
SGE_OPENCL_DETAIL_SYMBOL program::source_string_sequence
file_to_source_string_sequence(
	boost::filesystem::path const &);
}
}
}

#endif
