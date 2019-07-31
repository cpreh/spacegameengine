//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/draw_context.hpp>
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
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::draw_context::draw_context(
	sge::opengl::info::context const &_info
)
:
	sge::opengl::context::base(),
	draw_range_elements_(
		sge::opengl::info::version_at_least(
			_info.version(),
			sge::opengl::info::major_version{
				1u
			},
			sge::opengl::info::minor_version{
				2u
			}
		)
		?
			optional_draw_range_elements(
				sge::opengl::deref_fun_ptr(
					sge::opengl::info::cast_function<
						PFNGLDRAWRANGEELEMENTSPROC
					>(
						_info.load_function(
							"glDrawRangeElements"
						)
					)
				)
			)
		:
			sge::opengl::info::extension_supported(
				_info.extensions(),
				sge::opengl::info::extension{
					"GL_EXT_draw_range_elements"
				}
			)
			?
				optional_draw_range_elements(
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLDRAWRANGEELEMENTSPROC
						>(
							_info.load_function(
								"glDrawRangeElementsEXT"
							)
						)
					)
				)
			:
				optional_draw_range_elements()
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::draw_context::~draw_context()
{
}

sge::opengl::draw_context::optional_draw_range_elements
sge::opengl::draw_context::draw_range_elements() const
{
	return
		draw_range_elements_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::draw_context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
