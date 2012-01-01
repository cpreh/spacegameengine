/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_GLSL_TO_CVV_HPP_INCLUDED
#define SGE_RENDERER_GLSL_TO_CVV_HPP_INCLUDED

#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/symbol.hpp>

namespace sge
{
namespace renderer
{
namespace glsl
{

/**
 * \brief Transforms a matrix to the canonical view volume
 *
 * sge's canonical view volume is defined from (-1,-1,0) at the lower left
 * front to (1,1,1) at the upper right back. opengl uses a different ccv, which
 * this function transform to. The ccv mainly affects the mapping of the depth
 * buffer.
 *
 * \param matrix The projection matrix to transform
 *
 * \return The transformed matrix suitable for glsl
*/
SGE_RENDERER_SYMBOL
sge::renderer::matrix4 const
to_cvv(
	sge::renderer::matrix4 const &matrix
);

}
}
}

#endif
