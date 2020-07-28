//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/fbo/error_string_map.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>
#include <sge/opengl/fbo/optional_config.hpp>
#include <sge/opengl/info/cast_function.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::fbo::context::context(
	sge::opengl::info::context const &_info
)
:
	sge::opengl::context::base(),
	config_(
		sge::opengl::info::version_at_least(
			_info.version(),
			sge::opengl::info::major_version{
				3U
			},
			sge::opengl::info::minor_version{
				0U
			}
		)
		?
			sge::opengl::fbo::optional_config(
				sge::opengl::fbo::config(
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLGENFRAMEBUFFERSPROC
						>(
							_info.load_function(
								"glGenFramebuffers"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLDELETEFRAMEBUFFERSPROC
						>(
							_info.load_function(
								"glDeleteFramebuffers"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLBINDFRAMEBUFFERPROC
						>(
							_info.load_function(
								"glBindFramebuffer"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLFRAMEBUFFERTEXTURE2DPROC
						>(
							_info.load_function(
								"glFramebufferTexture2D"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLCHECKFRAMEBUFFERSTATUSPROC
						>(
							_info.load_function(
								"glCheckFramebufferStatus"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLGENRENDERBUFFERSPROC
						>(
							_info.load_function(
								"glGenRenderbuffers"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLDELETERENDERBUFFERSPROC
						>(
							_info.load_function(
								"glDeleteRenderbuffers"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLBINDRENDERBUFFERPROC
						>(
							_info.load_function(
								"glBindRenderbuffer"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLRENDERBUFFERSTORAGEPROC
						>(
							_info.load_function(
								"glRenderbufferStorage"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLFRAMEBUFFERRENDERBUFFERPROC
						>(
							_info.load_function(
								"glFramebufferRenderbuffer"
							)
						)
					),
					sge::opengl::convert::to_gl_enum<
						GL_FRAMEBUFFER
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_COLOR_ATTACHMENT0
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_FRAMEBUFFER_COMPLETE
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_FRAMEBUFFER_UNSUPPORTED
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_RENDERBUFFER
					>(),
					sge::opengl::fbo::attachment_type{
						sge::opengl::convert::to_gl_enum<
							GL_DEPTH_ATTACHMENT
						>()
					},
					sge::opengl::fbo::optional_attachment_type{
						sge::opengl::fbo::attachment_type{
							sge::opengl::convert::to_gl_enum<
								GL_DEPTH_STENCIL_ATTACHMENT
							>()
						}
					}
				)
			)
		:
			sge::opengl::info::extension_supported(
				_info.extensions(),
				sge::opengl::info::extension{
					"GL_EXT_framebuffer_object"
				}
			)
			?
				sge::opengl::fbo::optional_config(
					sge::opengl::fbo::config(
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLGENFRAMEBUFFERSPROC
							>(
								_info.load_function(
									"glGenFramebuffersEXT"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLDELETEFRAMEBUFFERSPROC
							>(
								_info.load_function(
									"glDeleteFramebuffersEXT"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLBINDFRAMEBUFFERPROC
							>(
								_info.load_function(
									"glBindFramebufferEXT"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLFRAMEBUFFERTEXTURE2DPROC
							>(
								_info.load_function(
									"glFramebufferTexture2DEXT"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLCHECKFRAMEBUFFERSTATUSPROC
							>(
								_info.load_function(
									"glCheckFramebufferStatusEXT"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLGENRENDERBUFFERSPROC
							>(
								_info.load_function(
									"glGenRenderbuffersEXT"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLDELETERENDERBUFFERSPROC
							>(
								_info.load_function(
									"glDeleteRenderbuffersEXT"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLBINDRENDERBUFFERPROC
							>(
								_info.load_function(
									"glBindRenderbufferEXT"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLRENDERBUFFERSTORAGEPROC
							>(
								_info.load_function(
									"glRenderbufferStorageEXT"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLFRAMEBUFFERRENDERBUFFERPROC
							>(
								_info.load_function(
									"glFramebufferRenderbufferEXT"
								)
							)
						),
						sge::opengl::convert::to_gl_enum<
							GL_FRAMEBUFFER_EXT
						>(),
						sge::opengl::convert::to_gl_enum<
							GL_COLOR_ATTACHMENT0_EXT
						>(),
						sge::opengl::convert::to_gl_enum<
							GL_FRAMEBUFFER_COMPLETE_EXT
						>(),
						sge::opengl::convert::to_gl_enum<
							GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT
						>(),
						sge::opengl::convert::to_gl_enum<
							GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT
						>(),
						sge::opengl::convert::to_gl_enum<
							GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT
						>(),
						sge::opengl::convert::to_gl_enum<
							GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT
						>(),
						sge::opengl::convert::to_gl_enum<
							GL_FRAMEBUFFER_UNSUPPORTED_EXT
						>(),
						sge::opengl::convert::to_gl_enum<
							GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT
						>(),
						sge::opengl::convert::to_gl_enum<
							GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT
						>(),
						sge::opengl::convert::to_gl_enum<
							GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT
						>(),
						sge::opengl::convert::to_gl_enum<
							GL_RENDERBUFFER_EXT
						>(),
						sge::opengl::fbo::attachment_type{
							sge::opengl::convert::to_gl_enum<
								GL_DEPTH_ATTACHMENT_EXT
							>()
						},
						sge::opengl::fbo::optional_attachment_type{}
					)
				)
			:
				sge::opengl::fbo::optional_config{}
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::fbo::context::~context()
= default;

sge::opengl::fbo::optional_config const &
sge::opengl::fbo::context::config() const
{
	return
		config_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::fbo::context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
