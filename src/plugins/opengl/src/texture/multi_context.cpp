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
#include <sge/opengl/get_int.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/convert/from_gl_bool.hpp>
#include <sge/opengl/texture/multi_config.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/opengl/texture/optional_multi_config.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::texture::multi_context::multi_context()
:
	sge::opengl::context::system::base(),
	config_(
		sge::opengl::convert::from_gl_bool(
			GLEW_VERSION_1_3
		)
		?
			sge::opengl::texture::optional_multi_config(
				sge::opengl::texture::multi_config(
					sge::opengl::deref_fun_ptr(
						glActiveTexture
					),
					sge::opengl::deref_fun_ptr(
						glClientActiveTexture
					),
					fcppt::strong_typedef_construct_cast<
						sge::renderer::caps::texture_stages,
						fcppt::cast::static_cast_fun
					>(
						std::min(
							sge::opengl::get_int(
								GL_MAX_TEXTURE_COORDS
							),
							sge::opengl::get_int(
								GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
							)
						)
					)
				)
			)
		:
			sge::opengl::convert::from_gl_bool(
				GLEW_ARB_multitexture
			)
			?
				sge::opengl::texture::optional_multi_config(
					sge::opengl::texture::multi_config(
						sge::opengl::deref_fun_ptr(
							glActiveTextureARB
						),
						sge::opengl::deref_fun_ptr(
							glClientActiveTextureARB
						),
						fcppt::strong_typedef_construct_cast<
							sge::renderer::caps::texture_stages,
							fcppt::cast::static_cast_fun
						>(
							std::min(
								sge::opengl::get_int(
									GL_MAX_TEXTURE_COORDS_ARB
								),
								sge::opengl::get_int(
									GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB
								)
							)
						)
					)
				)
			:
				sge::opengl::texture::optional_multi_config()
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::texture::multi_context::~multi_context()
{
}

sge::opengl::texture::optional_multi_config const &
sge::opengl::texture::multi_context::config() const
{
	return
		config_;
}

sge::opengl::context::system::id const
sge::opengl::texture::multi_context::static_id(
	sge::opengl::context::system::make_id()
);
