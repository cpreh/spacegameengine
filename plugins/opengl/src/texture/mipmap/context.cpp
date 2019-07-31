//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/info/cast_function.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/texture/mipmap/context.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


sge::opengl::texture::mipmap::context::context(
	sge::opengl::info::context const &_info
)
:
	sge::opengl::context::base(),
	generate_mipmap_flag_(
		sge::opengl::info::version_at_least(
			_info.version(),
			sge::opengl::info::major_version{
				1u
			},
			sge::opengl::info::minor_version{
				4u
			}
		)
		?
			sge::opengl::optional_enum(
				sge::opengl::convert::to_gl_enum<
					GL_GENERATE_MIPMAP
				>()
			)
		:
			sge::opengl::optional_enum()
	),
	generate_mipmap_(
		sge::opengl::info::version_at_least(
			_info.version(),
			sge::opengl::info::major_version{
				3u
			},
			sge::opengl::info::minor_version{
				0u
			}
		)
		?
			optional_gl_generate_mipmap(
				sge::opengl::deref_fun_ptr(
					sge::opengl::info::cast_function<
						PFNGLGENERATEMIPMAPPROC
					>(
						_info.load_function(
							"glGenerateMipmap"
						)
					)
				)
			)
		:
			optional_gl_generate_mipmap()
	)
{
}

sge::opengl::texture::mipmap::context::~context()
{
}

sge::opengl::optional_enum
sge::opengl::texture::mipmap::context::generate_mipmap_flag() const
{
	return
		generate_mipmap_flag_;
}

sge::opengl::texture::mipmap::context::optional_gl_generate_mipmap const &
sge::opengl::texture::mipmap::context::generate_mipmap() const
{
	return
		generate_mipmap_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::texture::mipmap::context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
