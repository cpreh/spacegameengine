/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_LOCK_RECT_TO_COORDS_HPP_INCLUDED
#define SGE_RENDERER_LOCK_RECT_TO_COORDS_HPP_INCLUDED

#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief Transforms a lock rect into texture coordinates
 *
 * Calculates the texture coordinates for \a area using the texture size \a
 * size.
 *
 * \param area The portion of the texture to calculate the coordinates for
 *
 * \param size The size of the texture
 *
 * \tparam Ret The floating point type for the resulting rect to use
 *
 * \return The texture coordinates in [(0,0),(1,1)]
 *
 * \warning The behaviour is undefined if \a area lies outside of \a size
*/
template<
	typename Ret
>
SGE_RENDERER_SYMBOL
typename boost::enable_if<
	boost::is_floating_point<
		Ret
	>,
	typename fcppt::math::box::rect<
		Ret
	>::type
>::type const
lock_rect_to_coords(
	renderer::lock_rect const &area,
	renderer::dim2 const &size
);

}
}

#endif
