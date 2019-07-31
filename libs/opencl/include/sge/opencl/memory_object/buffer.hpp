//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_MEMORY_OBJECT_BUFFER_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_BUFFER_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/memory_object/byte_size.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>
#include <sge/opencl/memory_object/renderer_buffer_lock_mode_fwd.hpp>
#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <fcppt/noncopyable.hpp>


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
	SGE_OPENCL_DETAIL_SYMBOL explicit
	buffer(
		opencl::context::object &,
		memory_object::flags_field const &,
		memory_object::byte_size const &);

	SGE_OPENCL_DETAIL_SYMBOL explicit
	buffer(
		opencl::context::object &,
		sge::renderer::vertex::buffer &,
		memory_object::renderer_buffer_lock_mode);

	SGE_OPENCL_DETAIL_SYMBOL cl_mem
	impl()
	override;

	SGE_OPENCL_DETAIL_SYMBOL memory_object::byte_size
	byte_size() const;

	SGE_OPENCL_DETAIL_SYMBOL ~buffer()
	override;
private:
	cl_mem impl_;
	memory_object::byte_size const byte_size_;
};
}
}
}

#endif
