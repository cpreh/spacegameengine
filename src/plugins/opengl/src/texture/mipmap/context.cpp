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

sge::opengl::context::id const
sge::opengl::texture::mipmap::context::static_id(
	sge::opengl::context::make_id()
);
