/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../build_mipmap.hpp"
#include "../../common.hpp"
#include "../../check_state.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture_creation_failed.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::texfuncs::build_mipmap(
	GLenum const tex_type,
	GLenum const format,
	GLenum const type,
	renderer::dim_type const &dim,
	renderer::const_raw_pointer const src
)
{
	if(!src)
		throw renderer::exception(
			FCPPT_TEXT("ogl::build_mipmaps: src is 0!")
		);

	gluBuild2DMipmaps(
		tex_type,
		format,
		static_cast<GLsizei>(dim.w()),
		static_cast<GLsizei>(dim.h()),
		format,
		type,
		src
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("gluBuild2DMipmaps failed"),
		sge::renderer::texture_creation_failed
	)
}
