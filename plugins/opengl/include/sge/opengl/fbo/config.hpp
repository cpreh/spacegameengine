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
	using
	gl_gen_framebuffers
	=
	sge::opengl::fun_ref<
		PFNGLGENFRAMEBUFFERSPROC
	>;

	using
	gl_delete_framebuffers
	=
	sge::opengl::fun_ref<
		PFNGLDELETEFRAMEBUFFERSPROC
	>;

	using
	gl_bind_framebuffer
	=
	sge::opengl::fun_ref<
		PFNGLBINDFRAMEBUFFERPROC
	>;

	using
	gl_framebuffer_texture_2d
	=
	sge::opengl::fun_ref<
		PFNGLFRAMEBUFFERTEXTURE2DPROC
	>;

	using
	gl_check_framebuffer_status
	=
	sge::opengl::fun_ref<
		PFNGLCHECKFRAMEBUFFERSTATUSPROC
	>;

	using
	gl_gen_renderbuffers
	=
	sge::opengl::fun_ref<
		PFNGLGENRENDERBUFFERSPROC
	>;

	using
	gl_delete_renderbuffers
	=
	sge::opengl::fun_ref<
		PFNGLDELETERENDERBUFFERSPROC
	>;

	using
	gl_bind_renderbuffer
	=
	sge::opengl::fun_ref<
		PFNGLBINDRENDERBUFFERPROC
	>;

	using
	gl_renderbuffer_storage
	=
	sge::opengl::fun_ref<
		PFNGLRENDERBUFFERSTORAGEPROC
	>;

	using
	gl_framebuffer_renderbuffer
	=
	sge::opengl::fun_ref<
		PFNGLFRAMEBUFFERRENDERBUFFERPROC
	>;

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

	[[nodiscard]]
	gl_gen_framebuffers
	gen_framebuffers() const;

	[[nodiscard]]
	gl_delete_framebuffers
	delete_framebuffers() const;

	[[nodiscard]]
	gl_bind_framebuffer
	bind_framebuffer() const;

	[[nodiscard]]
	gl_framebuffer_texture_2d
	framebuffer_texture_2d() const;

	[[nodiscard]]
	gl_check_framebuffer_status
	check_framebuffer_status() const;

	[[nodiscard]]
	gl_gen_renderbuffers
	gen_renderbuffers() const;

	[[nodiscard]]
	gl_delete_renderbuffers
	delete_renderbuffers() const;

	[[nodiscard]]
	gl_bind_renderbuffer
	bind_renderbuffer() const;

	[[nodiscard]]
	gl_renderbuffer_storage
	renderbuffer_storage() const;

	[[nodiscard]]
	gl_framebuffer_renderbuffer
	framebuffer_renderbuffer() const;

	[[nodiscard]]
	GLenum
	framebuffer_target() const;

	[[nodiscard]]
	sge::opengl::fbo::attachment_type
	color_attachment() const;

	[[nodiscard]]
	GLenum
	framebuffer_complete() const;

	[[nodiscard]]
	sge::opengl::fbo::error_string_map const &
	error_strings() const;

	[[nodiscard]]
	GLenum
	renderbuffer_target() const;

	[[nodiscard]]
	sge::opengl::fbo::attachment_type
	depth_attachment() const;

	[[nodiscard]]
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
