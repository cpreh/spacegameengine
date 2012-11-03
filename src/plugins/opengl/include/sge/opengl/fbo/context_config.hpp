/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENGL_FBO_CONTEXT_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_FBO_CONTEXT_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/context_config_fwd.hpp>
#include <sge/opengl/fbo/error_string_map.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace opengl
{
namespace fbo
{

class context_config
{
	FCPPT_NONASSIGNABLE(
		context_config
	);
public:
	typedef PFNGLGENFRAMEBUFFERSPROC gl_gen_framebuffers;

	typedef PFNGLDELETEFRAMEBUFFERSPROC gl_delete_framebuffers;

	typedef PFNGLBINDFRAMEBUFFERPROC gl_bind_framebuffer;

	typedef PFNGLFRAMEBUFFERTEXTURE2DPROC gl_framebuffer_texture_2d;

	typedef PFNGLCHECKFRAMEBUFFERSTATUSPROC gl_check_framebuffer_status;

	typedef PFNGLGENRENDERBUFFERSPROC gl_gen_renderbuffers;

	typedef PFNGLDELETERENDERBUFFERSPROC gl_delete_renderbuffers;

	typedef PFNGLBINDRENDERBUFFERPROC gl_bind_renderbuffer;

	typedef PFNGLRENDERBUFFERSTORAGEPROC gl_renderbuffer_storage;

	typedef PFNGLFRAMEBUFFERRENDERBUFFERPROC gl_framebuffer_renderbuffer;

	context_config(
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

	gl_gen_framebuffers const gen_framebuffers_;

	gl_delete_framebuffers const delete_framebuffers_;

	gl_bind_framebuffer const bind_framebuffer_;

	gl_framebuffer_texture_2d const framebuffer_texture_2d_;

	gl_check_framebuffer_status const check_framebuffer_status_;

	gl_gen_renderbuffers const gen_renderbuffers_;

	gl_delete_renderbuffers const delete_renderbuffers_;

	gl_bind_renderbuffer const bind_renderbuffer_;

	gl_renderbuffer_storage const renderbuffer_storage_;

	gl_framebuffer_renderbuffer const framebuffer_renderbuffer_;

	GLenum const framebuffer_target_;

	sge::opengl::fbo::attachment_type const color_attachment_;

	GLenum const fbo_complete_;

	sge::opengl::fbo::error_string_map const error_strings_;

	GLenum const renderbuffer_target_;

	sge::opengl::fbo::attachment_type const depth_attachment_;

	sge::opengl::fbo::optional_attachment_type const depth_stencil_attachment_;
};

}
}
}

#endif
