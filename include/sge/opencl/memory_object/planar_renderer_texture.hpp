#ifndef SGE_OPENCL_MEMORY_OBJECT_PLANAR_RENDERER_TEXTURE_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_PLANAR_RENDERER_TEXTURE_HPP_INCLUDED

#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/memory_object/renderer_buffer_lock_mode.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/class_symbol.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
class SGE_CLASS_SYMBOL planar_renderer_texture
:
	public memory_object::base
{
FCPPT_NONCOPYABLE(
	planar_renderer_texture);
public:
	explicit
	planar_renderer_texture(
		context::object &,
		sge::renderer::texture::planar &,
		sge::opencl::memory_object::renderer_buffer_lock_mode::type);

	cl_mem
	impl();

	~planar_renderer_texture();
private:
	cl_mem impl_;
};
}
}
}

#endif
