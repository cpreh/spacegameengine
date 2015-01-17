/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/convert/from_gl_bool.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/fbo/error_string_map.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::fbo::context::context()
:
	sge::opengl::context::system::base(),
	config_(
		sge::opengl::convert::from_gl_bool(
			GLEW_VERSION_3_0
		)
		?
			sge::opengl::fbo::context::optional_context_config(
				sge::opengl::fbo::context_config(
					glGenFramebuffers,
					glDeleteFramebuffers,
					glBindFramebuffer,
					glFramebufferTexture2D,
					glCheckFramebufferStatus,
					glGenRenderbuffers,
					glDeleteRenderbuffers,
					glBindRenderbuffer,
					glRenderbufferStorage,
					glFramebufferRenderbuffer,
					static_cast<
						GLenum
					>(
						GL_FRAMEBUFFER
					),
					static_cast<
						GLenum
					>(
						GL_COLOR_ATTACHMENT0
					),
					static_cast<
						GLenum
					>(
						GL_FRAMEBUFFER_COMPLETE
					),
					static_cast<
						GLenum
					>(
						GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
					),
					static_cast<
						GLenum
					>(
						GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
					),
					static_cast<
						GLenum
					>(
						GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER
					),
					static_cast<
						GLenum
					>(
						GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER
					),
					static_cast<
						GLenum
					>(
						GL_FRAMEBUFFER_UNSUPPORTED
					),
					static_cast<
						GLenum
					>(
						GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE
					),
					static_cast<
						GLenum
					>(
						GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE
					),
					static_cast<
						GLenum
					>(
						GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
					),
					static_cast<
						GLenum
					>(
						GL_RENDERBUFFER
					),
					fcppt::strong_typedef_construct_cast<
						sge::opengl::fbo::attachment_type
					>(
						GL_DEPTH_ATTACHMENT
					),
					sge::opengl::fbo::optional_attachment_type(
						fcppt::strong_typedef_construct_cast<
							sge::opengl::fbo::attachment_type
						>(
							GL_DEPTH_STENCIL_ATTACHMENT
						)
					)
				)
			)
		:
			sge::opengl::convert::from_gl_bool(
				GLEW_EXT_framebuffer_object
			)
			?
				sge::opengl::fbo::context::optional_context_config(
					sge::opengl::fbo::context_config(
						glGenFramebuffersEXT,
						glDeleteFramebuffersEXT,
						glBindFramebufferEXT,
						glFramebufferTexture2DEXT,
						glCheckFramebufferStatusEXT,
						glGenRenderbuffersEXT,
						glDeleteRenderbuffersEXT,
						glBindRenderbufferEXT,
						glRenderbufferStorageEXT,
						glFramebufferRenderbufferEXT,
						static_cast<
							GLenum
						>(
							GL_FRAMEBUFFER_EXT
						),
						static_cast<
							GLenum
						>(
							GL_COLOR_ATTACHMENT0_EXT
						),
						static_cast<
							GLenum
						>(
							GL_FRAMEBUFFER_COMPLETE_EXT
						),
						static_cast<
							GLenum
						>(
							GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT
						),
						static_cast<
							GLenum
						>(
							GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT
						),
						static_cast<
							GLenum
						>(
							GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT
						),
						static_cast<
							GLenum
						>(
							GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT
						),
						static_cast<
							GLenum
						>(
							GL_FRAMEBUFFER_UNSUPPORTED_EXT
						),
						static_cast<
							GLenum
						>(
							GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT
						),
						static_cast<
							GLenum
						>(
							GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT
						),
						static_cast<
							GLenum
						>(
							GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT
						),
						static_cast<
							GLenum
						>(
							GL_RENDERBUFFER_EXT
						),
						fcppt::strong_typedef_construct_cast<
							sge::opengl::fbo::attachment_type
						>(
							GL_DEPTH_ATTACHMENT_EXT
						),
						sge::opengl::fbo::optional_attachment_type()
					)
				)
			:
				sge::opengl::fbo::context::optional_context_config()
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::fbo::context::~context()
{
}

bool
sge::opengl::fbo::context::is_supported() const
{
	return
		config_.has_value();
}

sge::opengl::fbo::context::gl_gen_framebuffers
sge::opengl::fbo::context::gen_framebuffers() const
{
	return config_->gen_framebuffers_;
}

sge::opengl::fbo::context::gl_delete_framebuffers
sge::opengl::fbo::context::delete_framebuffers() const
{
	return config_->delete_framebuffers_;
}

sge::opengl::fbo::context::gl_bind_framebuffer
sge::opengl::fbo::context::bind_framebuffer() const
{
	return config_->bind_framebuffer_;
}

sge::opengl::fbo::context::gl_framebuffer_texture_2d
sge::opengl::fbo::context::framebuffer_texture_2d() const
{
	return config_->framebuffer_texture_2d_;
}

sge::opengl::fbo::context::gl_check_framebuffer_status
sge::opengl::fbo::context::check_framebuffer_status() const
{
	return config_->check_framebuffer_status_;
}

sge::opengl::fbo::context::gl_gen_renderbuffers
sge::opengl::fbo::context::gen_renderbuffers() const
{
	return config_->gen_renderbuffers_;
}

sge::opengl::fbo::context::gl_delete_renderbuffers
sge::opengl::fbo::context::delete_renderbuffers() const
{
	return config_->delete_renderbuffers_;
}

sge::opengl::fbo::context::gl_bind_renderbuffer
sge::opengl::fbo::context::bind_renderbuffer() const
{
	return config_->bind_renderbuffer_;
}

sge::opengl::fbo::context::gl_renderbuffer_storage
sge::opengl::fbo::context::renderbuffer_storage() const
{
	return config_->renderbuffer_storage_;
}

sge::opengl::fbo::context::gl_framebuffer_renderbuffer
sge::opengl::fbo::context::framebuffer_renderbuffer() const
{
	return config_->framebuffer_renderbuffer_;
}

GLenum
sge::opengl::fbo::context::framebuffer_target() const
{
	return config_->framebuffer_target_;
}

sge::opengl::fbo::attachment_type const
sge::opengl::fbo::context::color_attachment() const
{
	return config_->color_attachment_;
}

GLenum
sge::opengl::fbo::context::framebuffer_complete() const
{
	return config_->fbo_complete_;
}

sge::opengl::fbo::error_string_map const &
sge::opengl::fbo::context::error_strings() const
{
	return config_->error_strings_;
}

GLenum
sge::opengl::fbo::context::renderbuffer_target() const
{
	return config_->renderbuffer_target_;
}

sge::opengl::fbo::attachment_type const
sge::opengl::fbo::context::depth_attachment() const
{
	return config_->depth_attachment_;
}

sge::opengl::fbo::optional_attachment_type const
sge::opengl::fbo::context::depth_stencil_attachment() const
{
	return config_->depth_stencil_attachment_;
}

sge::opengl::context::system::id const
sge::opengl::fbo::context::static_id(
	sge::opengl::context::system::make_id()
);
