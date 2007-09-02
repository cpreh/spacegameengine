/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <iostream>
#include "../../../exception.hpp"
#include "../multi_texture.hpp"
#include "../common.hpp"
#include "../extension.hpp"

void sge::ogl::set_texture_level(const stage_type stage)
{
	if(!glActiveTextureARB)
		throw exception(extension_not_supported_string("ARB_multitexture"));
	if(stage >= GL_MAX_TEXTURE_UNITS_ARB)
	{
		std::cerr << "GL_MAX_TEXTURE_UNITS_ARB is " << GL_MAX_TEXTURE_UNITS_ARB << ". Setting texture stage " << stage << " ignored!\n";
		return;
	}

	glActiveTextureARB(static_cast<GLenum>(GL_TEXTURE0_ARB + stage));
}
