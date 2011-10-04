#ifndef SGE_OPENCL_MEMORY_OBJECT_BUFFER_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_BUFFER_HPP_INCLUDED

#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/memory_object/byte_size.hpp>
#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/symbol.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
class buffer
:
	public memory_object::base
{
FCPPT_NONCOPYABLE(
	buffer);
public:
	SGE_OPENCL_SYMBOL explicit
	buffer(
		opencl::context::object &,
		memory_object::flags_field const &,
		memory_object::byte_size const &);

	SGE_OPENCL_SYMBOL cl_mem
	impl();

	SGE_OPENCL_SYMBOL ~buffer();
private:
	cl_mem impl_;
};
}
}
}

#endif
