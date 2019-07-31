//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_MEMORY_OBJECT_FLAGS_FIELD_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_FLAGS_FIELD_HPP_INCLUDED

#include <sge/opencl/memory_object/flags.hpp>
#include <fcppt/container/bitfield/enum_object_fwd.hpp>


namespace sge
{
namespace opencl
{
namespace memory_object
{

// TODO: fwd header!
typedef
fcppt::container::bitfield::enum_object<
	sge::opencl::memory_object::flags
>
flags_field;

}
}
}

#endif
