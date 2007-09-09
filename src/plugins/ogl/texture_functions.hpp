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


#ifndef SGE_OGL_TEXTURE_FUNCTIONS_HPP_INCLUDED
#define SGE_OGL_TEXTURE_FUNCTIONS_HPP_INCLUDED

#include "../../renderer/texture.hpp"
#include "../../renderer/types.hpp"
#include "common.hpp"

namespace sge
{
namespace ogl
{

void set_texture_rect(GLenum type, const filter_args& filter, sge::texture_base::size_type width, sge::texture_base::size_type height, const lock_rect*, sge::texture_base::const_pointer src);

}
}

#endif
