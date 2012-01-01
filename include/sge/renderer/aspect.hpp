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


#ifndef SGE_RENDERER_ASPECT_HPP_INCLUDED
#define SGE_RENDERER_ASPECT_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/symbol.hpp>

namespace sge
{
namespace renderer
{

/**
 * \brief Calculates the aspect
 *
 * An aspect of a dimension (w,h) is defined as the ratio from the larger to
 * the smaller. The division is done as a floating point division.
 *
 * \param size The size to calculate the aspect from
 *
 * \return <code> size.w > size.h ? size.w / size.h : size.h / size.w </code>
 *
 * \warning The behaviour is undefined if either width or height is zero.
 */
SGE_RENDERER_SYMBOL
renderer::scalar
aspect(
	renderer::screen_size const &size
);

}
}

#endif
