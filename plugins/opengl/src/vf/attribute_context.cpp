//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/info/cast_function.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/vf/attribute_config.hpp>
#include <sge/opengl/vf/attribute_context.hpp>
#include <sge/opengl/vf/optional_attribute_config.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opengl::vf::attribute_context::attribute_context(
	sge::opengl::info::context const &_info
)
:
	sge::opengl::context::base(),
	config_(
		sge::opengl::info::version_at_least(
			_info.version(),
			sge::opengl::info::major_version{
				2U
			},
			sge::opengl::info::minor_version{
				0U
			}
		)
		?
			sge::opengl::vf::optional_attribute_config(
				sge::opengl::vf::attribute_config(
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLVERTEXATTRIBPOINTERPROC
						>(
							_info.load_function(
								"glVertexAttribPointer"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLENABLEVERTEXATTRIBARRAYPROC
						>(
							_info.load_function(
								"glEnableVertexAttribArray"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLDISABLEVERTEXATTRIBARRAYPROC
						>(
							_info.load_function(
								"glDisableVertexAttribArray"
							)
						)
					)
				)
			)
		:
			sge::opengl::info::extension_supported(
				_info.extensions(),
				sge::opengl::info::extension{
					"GL_ARB_vertex_shader"
				}
			)
			?
				sge::opengl::vf::optional_attribute_config(
					sge::opengl::vf::attribute_config(
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLVERTEXATTRIBPOINTERPROC
							>(
								_info.load_function(
									"glVertexAttribPointerARB"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLENABLEVERTEXATTRIBARRAYPROC
							>(
								_info.load_function(
									"glEnableVertexAttribArrayARB"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLDISABLEVERTEXATTRIBARRAYPROC
							>(
								_info.load_function(
									"glDisableVertexAttribArrayARB"
								)
							)
						)
					)
				)
			:
				sge::opengl::vf::optional_attribute_config()
	)
{
}

sge::opengl::vf::attribute_context::~attribute_context()
= default;

sge::opengl::vf::optional_attribute_config const &
sge::opengl::vf::attribute_context::config() const
{
	return
		config_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::vf::attribute_context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
