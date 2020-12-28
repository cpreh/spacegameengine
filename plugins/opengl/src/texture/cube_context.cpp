//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/texture/cube_config.hpp>
#include <sge/opengl/texture/cube_context.hpp>
#include <sge/opengl/texture/cube_side_array.hpp>
#include <sge/opengl/texture/optional_cube_config.hpp>
#include <sge/opengl/texture/convert/make_buffer_type.hpp>
#include <sge/opengl/texture/convert/make_type.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

// NOLINTNEXTLINE(cert-err58-cpp)
sge::opengl::texture::cube_side_array const normal_sides{
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_POSITIVE_X
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
	)
};

// NOLINTNEXTLINE(cert-err58-cpp)
sge::opengl::texture::cube_side_array const arb_sides{
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB
	),
	sge::opengl::texture::convert::make_buffer_type(
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB
	)
};

FCPPT_PP_POP_WARNING
}

sge::opengl::texture::cube_context::cube_context(
	sge::opengl::info::context const  &_info
)
:
	sge::opengl::context::base(),
	config_(
		sge::opengl::info::version_at_least(
			_info.version(),
			sge::opengl::info::major_version{
				1U
			},
			sge::opengl::info::minor_version{
				0U
			}
		)
		?
			sge::opengl::texture::optional_cube_config(
				sge::opengl::texture::cube_config(
					sge::opengl::texture::convert::make_type(
						GL_TEXTURE_CUBE_MAP
					),
					::normal_sides
				)
			)
		:
			sge::opengl::info::extension_supported(
				_info.extensions(),
				sge::opengl::info::extension{
					"GL_ARB_texture_cube_map"
				}
			)
			?
				sge::opengl::texture::optional_cube_config(
					sge::opengl::texture::cube_config(
						sge::opengl::texture::convert::make_type(
							GL_TEXTURE_CUBE_MAP_ARB
						),
						::arb_sides
					)
				)
			:
				sge::opengl::texture::optional_cube_config()
	)
{
}

sge::opengl::texture::cube_context::~cube_context()
= default;

sge::opengl::texture::optional_cube_config const &
sge::opengl::texture::cube_context::config() const
{
	return
		config_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
sge::opengl::texture::cube_context::static_id(
	sge::opengl::context::make_id()
);

FCPPT_PP_POP_WARNING
