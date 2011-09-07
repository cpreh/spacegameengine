#include "../handle_error.hpp"
#include "renderer_buffer_lock_mode_to_cl_mem_flags.hpp"
#include <sge/opencl/memory_object/planar_renderer_texture.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/opengl/texture/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <CL/cl_gl.h>
#include <fcppt/config/external_end.hpp>

sge::opencl::memory_object::planar_renderer_texture::planar_renderer_texture(
	context::object &_context,
	sge::renderer::texture::planar &_texture,
	sge::opencl::memory_object::renderer_buffer_lock_mode::type const _lock_mode)
:
	impl_(
		0)
{
	cl_int error_code;

	impl_ =
		clCreateFromGLTexture2D(
			_context.impl(),
			memory_object::renderer_buffer_lock_mode_to_cl_mem_flags(
				_lock_mode),
			GL_TEXTURE_2D,
			// FIXME: Is it ok to use 0 for the mipmap level in all cases?
			0,
			dynamic_cast<sge::renderer::opengl::texture::base &>(
				_texture).id().get(),
			&error_code);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clCreateFromGLBuffer"));
}

cl_mem
sge::opencl::memory_object::planar_renderer_texture::impl()
{
	return impl_;
}

sge::opencl::memory_object::planar_renderer_texture::~planar_renderer_texture()
{
	cl_int const error_code =
		clReleaseMemObject(
			impl_);

	opencl::handle_error(
		error_code,
		FCPPT_TEXT("clReleaseMemObject(planar renderer texture)"));
}
