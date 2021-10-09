//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_MEMORY_OBJECT_BASE_REF_SEQUENCE_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_BASE_REF_SEQUENCE_HPP_INCLUDED

#include <sge/opencl/memory_object/base_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::memory_object
{

using base_ref_sequence = std::vector<sge::opencl::memory_object::base_ref>;

}

#endif
