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


#ifndef SGE_RENDERER_TRANSFORM_HPP_INCLUDED
#define SGE_RENDERER_TRANSFORM_HPP_INCLUDED

#include "dim_types.hpp"
#include "screen_types.hpp"
#include "../su.hpp"
#include "../export.hpp"
#include "../math/rect.hpp"
#include "../math/matrix.hpp"

namespace sge
{
namespace renderer
{

SGE_SYMBOL math::space_matrix const
matrix_pixel_to_space(
	screen_size_t const &);

SGE_SYMBOL math::rect const
tex_size_to_space_rect(
	lock_rect const &l,
	dim_type const &dim,
	space_unit repeat = 1);

}
}

#endif
