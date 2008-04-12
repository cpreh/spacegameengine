/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../multi_texture.hpp"
#include "../common.hpp"
#include <sge/iostream.hpp>
#include <ostream>

void sge::ogl::set_texture_level(const stage_type stage)
{
	if(stage >= static_cast<stage_type>(std::max(GL_MAX_TEXTURE_COORDS, GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)))
	{
		sge::cerr << SGE_TEXT("GL_MAX_COMBINED_TEXTURE_UNITS is ") << GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS << SGE_TEXT(". Setting texture stage ") << stage << SGE_TEXT(" ignored!\n");
		return;
	}

	glActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + stage));
}
