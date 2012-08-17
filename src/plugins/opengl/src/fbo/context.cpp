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
#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::fbo::context::context()
:
	sge::opengl::context::system::base(),
	has_native_(
		GLEW_VERSION_3_0
	),
	has_ext_(
		GLEW_EXT_framebuffer_object
	),
	gen_framebuffers_(
		has_native_
		?
			glGenFramebuffers
		:
			has_ext_
			?
				glGenFramebuffersEXT
			:
				fcppt::null_ptr()
	),
	delete_framebuffers_(
		has_native_
		?
			glDeleteFramebuffers
		:
			has_ext_
			?
				glDeleteFramebuffersEXT
			:
				fcppt::null_ptr()
	),
	bind_framebuffer_(
		has_native_
		?
			glBindFramebuffer
		:
			has_ext_
			?
				glBindFramebufferEXT
			:
				fcppt::null_ptr()
	),
	framebuffer_texture_2d_(
		has_native_
		?
			glFramebufferTexture2D
		:
			has_ext_
			?
				glFramebufferTexture2DEXT
			:
				fcppt::null_ptr()
	),
	check_framebuffer_status_(
		has_native_
		?
			glCheckFramebufferStatus
		:
			has_ext_
			?
				glCheckFramebufferStatusEXT
			:
				fcppt::null_ptr()
	),
	gen_renderbuffers_(
		has_native_
		?
			glGenRenderbuffers
		:
			has_ext_
			?
				glGenRenderbuffersEXT
			:
				fcppt::null_ptr()
	),
	delete_renderbuffers_(
		has_native_
		?
			glDeleteRenderbuffers
		:
			has_ext_
			?
				glDeleteRenderbuffersEXT
			:
				fcppt::null_ptr()
	),
	bind_renderbuffer_(
		has_native_
		?
			glBindRenderbuffer
		:
			has_ext_
			?
				glBindRenderbufferEXT
			:
				fcppt::null_ptr()
	),
	renderbuffer_storage_(
		has_native_
		?
			glRenderbufferStorage
		:
			has_ext_
			?
				glRenderbufferStorageEXT
			:
				fcppt::null_ptr()
	),
	framebuffer_renderbuffer_(
		has_native_
		?
			glFramebufferRenderbuffer
		:
			has_ext_
			?
				glFramebufferRenderbufferEXT
			:
				fcppt::null_ptr()
	),
	framebuffer_target_(
		has_native_
		?
			sge::opengl::optional_enum(
				static_cast<
					GLenum
				>(
					GL_FRAMEBUFFER
				)
			)
		:
			has_ext_
			?
				sge::opengl::optional_enum(
					static_cast<
						GLenum
					>(
						GL_FRAMEBUFFER_EXT
					)
				)
			:
				sge::opengl::optional_enum()
	),
	color_attachment_(
		has_native_
		?
			sge::opengl::fbo::optional_attachment_type(
				fcppt::strong_typedef_construct_cast<
					sge::opengl::fbo::attachment_type
				>(
					GL_COLOR_ATTACHMENT0
				)
			)
		:
			has_ext_
			?
				sge::opengl::fbo::optional_attachment_type(
					fcppt::strong_typedef_construct_cast<
						sge::opengl::fbo::attachment_type
					>(
						GL_COLOR_ATTACHMENT0_EXT
					)
				)
			:
				sge::opengl::fbo::optional_attachment_type()
	),
	framebuffer_complete_(
		has_native_
		?
			sge::opengl::optional_enum(
				static_cast<
					GLenum
				>(
					GL_FRAMEBUFFER_COMPLETE
				)
			)
		:
			has_ext_
			?
				sge::opengl::optional_enum(
					static_cast<
						GLenum
					>(
						GL_FRAMEBUFFER_COMPLETE_EXT
					)
				)
			:
				sge::opengl::optional_enum()
	),
	renderbuffer_target_(
		has_native_
		?
			sge::opengl::optional_enum(
				static_cast<
					GLenum
				>(
					GL_RENDERBUFFER
				)
			)
		:
			has_ext_
			?
				sge::opengl::optional_enum(
					static_cast<
						GLenum
					>(
						GL_RENDERBUFFER_EXT
					)
				)
			:
				sge::opengl::optional_enum()
	),
	depth_attachment_(
		has_native_
		?
			sge::opengl::fbo::optional_attachment_type(
				fcppt::strong_typedef_construct_cast<
					sge::opengl::fbo::attachment_type
				>(
					GL_DEPTH_ATTACHMENT
				)
			)
		:
			has_ext_
			?
				sge::opengl::fbo::optional_attachment_type(
					fcppt::strong_typedef_construct_cast<
						sge::opengl::fbo::attachment_type
					>(
						GL_DEPTH_ATTACHMENT_EXT
					)
				)
			:
				sge::opengl::fbo::optional_attachment_type()
	),
	depth_stencil_attachment_(
		has_native_
		?
			sge::opengl::fbo::optional_attachment_type(
				fcppt::strong_typedef_construct_cast<
					sge::opengl::fbo::attachment_type
				>(
					GL_DEPTH_STENCIL_ATTACHMENT
				)
			)
		:
			sge::opengl::fbo::optional_attachment_type()
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
		has_native_
		|| has_ext_;
}

sge::opengl::fbo::context::gl_gen_framebuffers
sge::opengl::fbo::context::gen_framebuffers() const
{
	return gen_framebuffers_;
}

sge::opengl::fbo::context::gl_delete_framebuffers
sge::opengl::fbo::context::delete_framebuffers() const
{
	return delete_framebuffers_;
}

sge::opengl::fbo::context::gl_bind_framebuffer
sge::opengl::fbo::context::bind_framebuffer() const
{
	return bind_framebuffer_;
}

sge::opengl::fbo::context::gl_framebuffer_texture_2d
sge::opengl::fbo::context::framebuffer_texture_2d() const
{
	return framebuffer_texture_2d_;
}

sge::opengl::fbo::context::gl_check_framebuffer_status
sge::opengl::fbo::context::check_framebuffer_status() const
{
	return check_framebuffer_status_;
}

sge::opengl::fbo::context::gl_gen_renderbuffers
sge::opengl::fbo::context::gen_renderbuffers() const
{
	return gen_renderbuffers_;
}

sge::opengl::fbo::context::gl_delete_renderbuffers
sge::opengl::fbo::context::delete_renderbuffers() const
{
	return delete_renderbuffers_;
}

sge::opengl::fbo::context::gl_bind_renderbuffer
sge::opengl::fbo::context::bind_renderbuffer() const
{
	return bind_renderbuffer_;
}

sge::opengl::fbo::context::gl_renderbuffer_storage
sge::opengl::fbo::context::renderbuffer_storage() const
{
	return renderbuffer_storage_;
}

sge::opengl::fbo::context::gl_framebuffer_renderbuffer
sge::opengl::fbo::context::framebuffer_renderbuffer() const
{
	return framebuffer_renderbuffer_;
}

sge::opengl::optional_enum const
sge::opengl::fbo::context::framebuffer_target() const
{
	return framebuffer_target_;
}

sge::opengl::fbo::optional_attachment_type const
sge::opengl::fbo::context::color_attachment() const
{
	return color_attachment_;
}

sge::opengl::optional_enum const
sge::opengl::fbo::context::framebuffer_complete() const
{
	return framebuffer_complete_;
}

sge::opengl::optional_enum const
sge::opengl::fbo::context::renderbuffer_target() const
{
	return renderbuffer_target_;
}

sge::opengl::fbo::optional_attachment_type const
sge::opengl::fbo::context::depth_attachment() const
{
	return depth_attachment_;
}

sge::opengl::fbo::optional_attachment_type const
sge::opengl::fbo::context::depth_stencil_attachment() const
{
	return depth_stencil_attachment_;
}

sge::opengl::context::system::id const
sge::opengl::fbo::context::static_id(
	sge::opengl::context::system::make_id()
);
