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
#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/convert/from_gl_bool.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/fbo/error_string_map.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>
#include <sge/opengl/fbo/optional_config.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
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
			sge::opengl::fbo::optional_config(
				sge::opengl::fbo::config(
					sge::opengl::deref_fun_ptr(
						glGenFramebuffers
					),
					sge::opengl::deref_fun_ptr(
						glDeleteFramebuffers
					),
					sge::opengl::deref_fun_ptr(
						glBindFramebuffer
					),
					sge::opengl::deref_fun_ptr(
						glFramebufferTexture2D
					),
					sge::opengl::deref_fun_ptr(
						glCheckFramebufferStatus
					),
					sge::opengl::deref_fun_ptr(
						glGenRenderbuffers
					),
					sge::opengl::deref_fun_ptr(
						glDeleteRenderbuffers
					),
					sge::opengl::deref_fun_ptr(
						glBindRenderbuffer
					),
					sge::opengl::deref_fun_ptr(
						glRenderbufferStorage
					),
					sge::opengl::deref_fun_ptr(
						glFramebufferRenderbuffer
					),
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
						sge::opengl::fbo::attachment_type,
						fcppt::cast::static_cast_fun
					>(
						GL_DEPTH_ATTACHMENT
					),
					sge::opengl::fbo::optional_attachment_type(
						fcppt::strong_typedef_construct_cast<
							sge::opengl::fbo::attachment_type,
							fcppt::cast::static_cast_fun
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
				sge::opengl::fbo::optional_config(
					sge::opengl::fbo::config(
						sge::opengl::deref_fun_ptr(
							glGenFramebuffersEXT
						),
						sge::opengl::deref_fun_ptr(
							glDeleteFramebuffersEXT
						),
						sge::opengl::deref_fun_ptr(
							glBindFramebufferEXT
						),
						sge::opengl::deref_fun_ptr(
							glFramebufferTexture2DEXT
						),
						sge::opengl::deref_fun_ptr(
							glCheckFramebufferStatusEXT
						),
						sge::opengl::deref_fun_ptr(
							glGenRenderbuffersEXT
						),
						sge::opengl::deref_fun_ptr(
							glDeleteRenderbuffersEXT
						),
						sge::opengl::deref_fun_ptr(
							glBindRenderbufferEXT
						),
						sge::opengl::deref_fun_ptr(
							glRenderbufferStorageEXT
						),
						sge::opengl::deref_fun_ptr(
							glFramebufferRenderbufferEXT
						),
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
							sge::opengl::fbo::attachment_type,
							fcppt::cast::static_cast_fun
						>(
							GL_DEPTH_ATTACHMENT_EXT
						),
						sge::opengl::fbo::optional_attachment_type()
					)
				)
			:
				sge::opengl::fbo::optional_config()
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::fbo::context::~context()
{
}

sge::opengl::fbo::optional_config const &
sge::opengl::fbo::context::config() const
{
	return
		config_;
}

sge::opengl::context::system::id const
sge::opengl::fbo::context::static_id(
	sge::opengl::context::system::make_id()
);
