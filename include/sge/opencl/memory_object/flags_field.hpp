#ifndef SGE_OPENCL_MEMORY_OBJECT_FLAGS_FIELD_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_FLAGS_FIELD_HPP_INCLUDED

#include <sge/opencl/memory_object/flags.hpp>
#include <fcppt/container/bitfield/basic_fwd.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
typedef
fcppt::container::bitfield::basic
<
	memory_object::flags::type,
	memory_object::flags::size
>
flags_field;
}
}
}

#endif
