#ifndef SGE_OPENCL_MEMORY_OBJECT_IMAGE_VOLUME_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_VOLUME_HPP_INCLUDED

#include <sge/renderer/texture/volume_fwd.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/memory_object/dim3.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
namespace image
{
class volume
:
	public memory_object::base
{
FCPPT_NONCOPYABLE(
	volume);
public:
	SGE_OPENCL_SYMBOL explicit
	volume(
		context::object &,
		memory_object::flags_field const &,
		renderer::texture::volume &);

	SGE_OPENCL_SYMBOL cl_mem
	impl();

	SGE_OPENCL_SYMBOL cl_image_format const &
	image_format() const;

	SGE_OPENCL_SYMBOL memory_object::dim3 const &
	size() const;

	SGE_OPENCL_SYMBOL ~volume();
private:
	cl_mem impl_;
	cl_image_format image_format_;
	memory_object::dim3 size_;
};
}
}
}
}

#endif
