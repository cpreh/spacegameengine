/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/info/cast_function.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/texture/optional_volume_config.hpp>
#include <sge/opengl/texture/volume_config.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/opengl/texture/convert/make_type.hpp>


sge::opengl::texture::volume_context::volume_context(
	sge::opengl::info::context const &_info
)
:
	sge::opengl::context::base(),
	config_(
		sge::opengl::info::version_at_least(
			_info.version(),
			sge::opengl::info::major_version{
				1u
			},
			sge::opengl::info::minor_version{
				3u
			}
		)
		?
			sge::opengl::texture::optional_volume_config(
				sge::opengl::texture::volume_config(
					sge::opengl::texture::convert::make_type(
						GL_TEXTURE_3D
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLTEXIMAGE3DPROC
						>(
							_info.load_function(
								"glTexImage3D"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLTEXSUBIMAGE3DPROC
						>(
							_info.load_function(
								"glTexSubImage3D"
							)
						)
					),
					sge::opengl::convert::to_gl_enum<
						GL_MAX_3D_TEXTURE_SIZE
					>()
				)
			)
		:
			sge::opengl::texture::optional_volume_config()
	)
{
}

sge::opengl::texture::volume_context::~volume_context()
{
}

sge::opengl::texture::optional_volume_config const &
sge::opengl::texture::volume_context::config() const
{
	return
		config_;
}

sge::opengl::context::id const
sge::opengl::texture::volume_context::static_id(
	sge::opengl::context::make_id()
);
