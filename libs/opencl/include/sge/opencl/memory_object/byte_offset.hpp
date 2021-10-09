//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_MEMORY_OBJECT_BYTE_OFFSET_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_BYTE_OFFSET_HPP_INCLUDED

#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::memory_object
{

FCPPT_DECLARE_STRONG_TYPEDEF(std::size_t, byte_offset);

}

#endif
