/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/get_int.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/convert/from_gl_bool.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
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
	is_native_(
		sge::opengl::convert::from_gl_bool(
			GLEW_VERSION_1_3
		)
	),
	is_arb_(
		sge::opengl::convert::from_gl_bool(
			GLEW_ARB_multitexture
		)
	),
	active_texture_(
		is_native_
		?
			glActiveTexture
		:
			is_arb_
			?
				glActiveTextureARB
			:
				nullptr
	),
	client_active_texture_(
		is_native_
		?
			glClientActiveTexture
		:
			is_arb_
			?
				glClientActiveTextureARB
			:
				nullptr
	),
	max_level_(
		fcppt::strong_typedef_construct_cast<
			sge::renderer::caps::texture_stages
		>(
			is_native_
			?
				std::min(
					opengl::get_int(
						GL_MAX_TEXTURE_COORDS
					),
					opengl::get_int(
						GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
					)
				)
			:
				is_arb_
				?
					std::min(
						opengl::get_int(
							GL_MAX_TEXTURE_COORDS_ARB
						),
						opengl::get_int(
							GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB
						)
					)
				:
					1
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::texture::multi_context::~multi_context()
{
}

bool
sge::opengl::texture::multi_context::is_supported() const
{
	return
		is_native_
		|| is_arb_;
}

sge::opengl::texture::multi_context::gl_active_texture
sge::opengl::texture::multi_context::active_texture() const
{
	return active_texture_;
}

sge::opengl::texture::multi_context::gl_client_active_texture
sge::opengl::texture::multi_context::client_active_texture() const
{
	return client_active_texture_;
}

sge::renderer::caps::texture_stages const
sge::opengl::texture::multi_context::max_level() const
{
	return max_level_;
}

sge::opengl::context::system::id const
sge::opengl::texture::multi_context::static_id(
	sge::opengl::context::system::make_id()
);
