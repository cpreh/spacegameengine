#ifndef SGE_OPENCL_MEMORY_OBJECT_PLANAR_TEXTURE_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_PLANAR_TEXTURE_HPP_INCLUDED

#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/memory_object/dim2.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
class planar_texture
{
FCPPT_NONCOPYABLE(
	planar_texture);
public:
	explicit
	planar_texture(
		context::object &,
		cl_mem_flags,
		cl_image_format const &,
		memory_object::dim2 const &size,
		memory_object::dim2::value_type pitch);

	cl_mem
	impl();

	cl_image_format const &
	image_format() const;

	~planar_texture();
private:
	cl_mem impl_;
	cl_image_format const image_format_;
};
}
}
}

#endif
