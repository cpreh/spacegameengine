/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/fbo/config.hpp>
#include <sge/opengl/fbo/error_string_map.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_map.hpp>


sge::opengl::fbo::config::config(
	gl_gen_framebuffers _gen_framebuffers,
	gl_delete_framebuffers _delete_framebuffers,
	gl_bind_framebuffer _bind_framebuffer,
	gl_framebuffer_texture_2d _framebuffer_texture_2d,
	gl_check_framebuffer_status _check_framebuffer_status,
	gl_gen_renderbuffers _gen_renderbuffers,
	gl_delete_renderbuffers _delete_renderbuffers,
	gl_bind_renderbuffer _bind_renderbuffer,
	gl_renderbuffer_storage _renderbuffer_storage,
	gl_framebuffer_renderbuffer _framebuffer_renderbuffer,
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
	framebuffer_complete_(
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

sge::opengl::fbo::config::gl_gen_framebuffers
sge::opengl::fbo::config::gen_framebuffers() const
{
	return
		gen_framebuffers_;
}

sge::opengl::fbo::config::gl_delete_framebuffers
sge::opengl::fbo::config::delete_framebuffers() const
{
	return
		delete_framebuffers_;
}

sge::opengl::fbo::config::gl_bind_framebuffer
sge::opengl::fbo::config::bind_framebuffer() const
{
	return
		bind_framebuffer_;
}

sge::opengl::fbo::config::gl_framebuffer_texture_2d
sge::opengl::fbo::config::framebuffer_texture_2d() const
{
	return
		framebuffer_texture_2d_;
}

sge::opengl::fbo::config::gl_check_framebuffer_status
sge::opengl::fbo::config::check_framebuffer_status() const
{
	return
		check_framebuffer_status_;
}

sge::opengl::fbo::config::gl_gen_renderbuffers
sge::opengl::fbo::config::gen_renderbuffers() const
{
	return
		gen_renderbuffers_;
}

sge::opengl::fbo::config::gl_delete_renderbuffers
sge::opengl::fbo::config::delete_renderbuffers() const
{
	return
		delete_renderbuffers_;
}

sge::opengl::fbo::config::gl_bind_renderbuffer
sge::opengl::fbo::config::bind_renderbuffer() const
{
	return
		bind_renderbuffer_;
}

sge::opengl::fbo::config::gl_renderbuffer_storage
sge::opengl::fbo::config::renderbuffer_storage() const
{
	return
		renderbuffer_storage_;
}

sge::opengl::fbo::config::gl_framebuffer_renderbuffer
sge::opengl::fbo::config::framebuffer_renderbuffer() const
{
	return
		framebuffer_renderbuffer_;
}

GLenum
sge::opengl::fbo::config::framebuffer_target() const
{
	return
		framebuffer_target_;
}

sge::opengl::fbo::attachment_type
sge::opengl::fbo::config::color_attachment() const
{
	return
		color_attachment_;
}

GLenum
sge::opengl::fbo::config::framebuffer_complete() const
{
	return
		framebuffer_complete_;
}

sge::opengl::fbo::error_string_map const &
sge::opengl::fbo::config::error_strings() const
{
	return
		error_strings_;
}

GLenum
sge::opengl::fbo::config::renderbuffer_target() const
{
	return
		renderbuffer_target_;
}

sge::opengl::fbo::attachment_type
sge::opengl::fbo::config::depth_attachment() const
{
	return
		depth_attachment_;
}

sge::opengl::fbo::optional_attachment_type
sge::opengl::fbo::config::depth_stencil_attachment() const
{
	return
		depth_stencil_attachment_;
}
