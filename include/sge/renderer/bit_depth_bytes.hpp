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


#ifndef SGE_RENDERER_BIT_DEPTH_BYTES_HPP_INCLUDED
#define SGE_RENDERER_BIT_DEPTH_BYTES_HPP_INCLUDED

#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/symbol.hpp>

namespace sge
{
namespace renderer
{

/**
 * \brief Calculates how many bytes are needed for one pixel
 *
 * Calculates how many bytes are needed for a pixel
 * from \a bit_depth
 *
 * \param bit_depth The bit_depth to calculate the size from
 *
 * \return <code> sizeof(uint16_t) or sizeof(uint32_t) </code>
*/
SGE_RENDERER_SYMBOL
renderer::size_type
bit_depth_bytes(
	renderer::bit_depth::type bit_depth
);

}
}

#endif
