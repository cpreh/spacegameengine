//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_PROGRAM_SOURCE_STRING_SEQUENCE_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_SOURCE_STRING_SEQUENCE_HPP_INCLUDED

#include <sge/opencl/program/source_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::opencl::program
{

using
source_string_sequence
=
std::vector<
	sge::opencl::program::source_string
>;

}

#endif
