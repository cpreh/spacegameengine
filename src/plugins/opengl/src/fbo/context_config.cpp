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


#include <sge/opengl/common.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/context_config.hpp>
#include <sge/opengl/fbo/error_string_map.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_map.hpp>


sge::opengl::fbo::context_config::context_config(
	gl_gen_framebuffers const _gen_framebuffers,
	gl_delete_framebuffers const _delete_framebuffers,
	gl_bind_framebuffer const _bind_framebuffer,
	gl_framebuffer_texture_2d const _framebuffer_texture_2d,
	gl_check_framebuffer_status const _check_framebuffer_status,
	gl_gen_renderbuffers const _gen_renderbuffers,
	gl_delete_renderbuffers const _delete_renderbuffers,
	gl_bind_renderbuffer const _bind_renderbuffer,
	gl_renderbuffer_storage const _renderbuffer_storage,
	gl_framebuffer_renderbuffer const _framebuffer_renderbuffer,
	GLenum const _framebuffer_target,
	GLenum const _color_attachment,
	GLenum const _fbo_complete,
	GLenum const _fbo_undefined,
	GLenum const _fbo_incomplete_attachment,
	GLenum const _fbo_incomplete_missing_attachment,
	GLenum const _fbo_incomplete_draw_buffer,
	GLenum const _fbo_incomplete_read_buffer,
	GLenum const _fbo_unsupported,
	GLenum const _fbo_incomplete_multisample,
	GLenum const _fbo_incomplete_layer_targets,
	GLenum const _renderbuffer_target,
	sge::opengl::fbo::attachment_type const _depth_attachment,
	sge::opengl::fbo::optional_attachment_type const _depth_stencil_attachment
)
:
	gen_framebuffers_(
		_gen_framebuffers
	),
	delete_framebuffers_(
		_delete_framebuffers
	),
	bind_framebuffer_(
		_bind_framebuffer
	),
	framebuffer_texture_2d_(
		_framebuffer_texture_2d
	),
	check_framebuffer_status_(
		_check_framebuffer_status
	),
	gen_renderbuffers_(
		_gen_renderbuffers
	),
	delete_renderbuffers_(
		_delete_renderbuffers
	),
	bind_renderbuffer_(
		_bind_renderbuffer
	),
	renderbuffer_storage_(
		_renderbuffer_storage
	),
	framebuffer_renderbuffer_(
		_framebuffer_renderbuffer
	),
	framebuffer_target_(
		_framebuffer_target
	),
	color_attachment_(
		_color_attachment
	),
	fbo_complete_(
		_fbo_complete
	),
	error_strings_(
		fcppt::assign::make_map<
			sge::opengl::fbo::error_string_map
		>(
			_fbo_undefined,
			FCPPT_TEXT("undefined")
		)(
			_fbo_incomplete_attachment,
			FCPPT_TEXT("incomplete attachment")
		)(
			_fbo_incomplete_missing_attachment,
			FCPPT_TEXT("incomplete missing attachment")
		)(
			_fbo_incomplete_draw_buffer,
			FCPPT_TEXT("incomplete draw buffer")
		)(
			_fbo_incomplete_read_buffer,
			FCPPT_TEXT("incomplete read buffer")
		)(
			_fbo_unsupported,
			FCPPT_TEXT("unsupported")
		)(
			_fbo_incomplete_multisample,
			FCPPT_TEXT("incomplete multisample")
		)(
			_fbo_incomplete_layer_targets,
			FCPPT_TEXT("incomplete layer targets")
		)
	),
	renderbuffer_target_(
		_renderbuffer_target
	),
	depth_attachment_(
		_depth_attachment
	),
	depth_stencil_attachment_(
		_depth_stencil_attachment
	)
{
}
