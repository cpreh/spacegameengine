//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_FBO_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_FBO_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/fbo/error_string_map.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>


namespace sge
{
namespace opengl
{
namespace fbo
{

class config
{
public:
	typedef
	sge::opengl::fun_ref<
		PFNGLGENFRAMEBUFFERSPROC
	>
	gl_gen_framebuffers;

	typedef
	sge::opengl::fun_ref<
		PFNGLDELETEFRAMEBUFFERSPROC
	>
	gl_delete_framebuffers;

	typedef
	sge::opengl::fun_ref<
		PFNGLBINDFRAMEBUFFERPROC
	>
	gl_bind_framebuffer;

	typedef
	sge::opengl::fun_ref<
		PFNGLFRAMEBUFFERTEXTURE2DPROC
	>
	gl_framebuffer_texture_2d;

	typedef
	sge::opengl::fun_ref<
		PFNGLCHECKFRAMEBUFFERSTATUSPROC
	>
	gl_check_framebuffer_status;

	typedef
	sge::opengl::fun_ref<
		PFNGLGENRENDERBUFFERSPROC
	>
	gl_gen_renderbuffers;

	typedef
	sge::opengl::fun_ref<
		PFNGLDELETERENDERBUFFERSPROC
	>
	gl_delete_renderbuffers;

	typedef
	sge::opengl::fun_ref<
		PFNGLBINDRENDERBUFFERPROC
	>
	gl_bind_renderbuffer;

	typedef
	sge::opengl::fun_ref<
		PFNGLRENDERBUFFERSTORAGEPROC
	>
	gl_renderbuffer_storage;

	typedef
	sge::opengl::fun_ref<
		PFNGLFRAMEBUFFERRENDERBUFFERPROC
	>
	gl_framebuffer_renderbuffer;

	config(
		gl_gen_framebuffers,
		gl_delete_framebuffers,
		gl_bind_framebuffer,
		gl_framebuffer_texture_2d,
		gl_check_framebuffer_status,
		gl_gen_renderbuffers,
		gl_delete_renderbuffers,
		gl_bind_renderbuffer,
		gl_renderbuffer_storage,
		gl_framebuffer_renderbuffer,
		GLenum target,
		GLenum color_attachment,
		GLenum fbo_complete,
		GLenum fbo_undefined,
		GLenum fbo_incomplete_attachment,
		GLenum fbo_incomplete_missing_attachment,
		GLenum fbo_incomplete_draw_buffer,
		GLenum fbo_incomplete_read_buffer,
		GLenum fbo_unsupported,
		GLenum fbo_incomplete_multisample,
		GLenum fbo_incomplete_layer_targets,
		GLenum render_buffer_target,
		sge::opengl::fbo::attachment_type depth_attachment,
		sge::opengl::fbo::optional_attachment_type depth_stencil_attachment
	);

	gl_gen_framebuffers
	gen_framebuffers() const;

	gl_delete_framebuffers
	delete_framebuffers() const;

	gl_bind_framebuffer
	bind_framebuffer() const;

	gl_framebuffer_texture_2d
	framebuffer_texture_2d() const;

	gl_check_framebuffer_status
	check_framebuffer_status() const;

	gl_gen_renderbuffers
	gen_renderbuffers() const;

	gl_delete_renderbuffers
	delete_renderbuffers() const;

	gl_bind_renderbuffer
	bind_renderbuffer() const;

	gl_renderbuffer_storage
	renderbuffer_storage() const;

	gl_framebuffer_renderbuffer
	framebuffer_renderbuffer() const;

	GLenum
	framebuffer_target() const;

	sge::opengl::fbo::attachment_type
	color_attachment() const;

	GLenum
	framebuffer_complete() const;

	sge::opengl::fbo::error_string_map const &
	error_strings() const;

	GLenum
	renderbuffer_target() const;

	sge::opengl::fbo::attachment_type
	depth_attachment() const;

	sge::opengl::fbo::optional_attachment_type
	depth_stencil_attachment() const;
private:
	gl_gen_framebuffers gen_framebuffers_;

	gl_delete_framebuffers delete_framebuffers_;

	gl_bind_framebuffer bind_framebuffer_;

	gl_framebuffer_texture_2d framebuffer_texture_2d_;

	gl_check_framebuffer_status check_framebuffer_status_;

	gl_gen_renderbuffers gen_renderbuffers_;

	gl_delete_renderbuffers delete_renderbuffers_;

	gl_bind_renderbuffer bind_renderbuffer_;

	gl_renderbuffer_storage renderbuffer_storage_;

	gl_framebuffer_renderbuffer framebuffer_renderbuffer_;

	GLenum framebuffer_target_;

	sge::opengl::fbo::attachment_type color_attachment_;

	GLenum framebuffer_complete_;

	sge::opengl::fbo::error_string_map error_strings_;

	GLenum renderbuffer_target_;

	sge::opengl::fbo::attachment_type depth_attachment_;

	sge::opengl::fbo::optional_attachment_type depth_stencil_attachment_;
};

}
}
}

#endif
