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


#ifndef SGE_RENDERER_LOCK_RECT_TO_COORDS_HPP_INCLUDED
#define SGE_RENDERER_LOCK_RECT_TO_COORDS_HPP_INCLUDED

#include <sge/renderer/dim2_fwd.hpp>
#include <sge/renderer/lock_rect_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/type_traits/is_float_or_double.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{

/**
\brief Transforms a lock rect into texture coordinates

\ingroup sge_renderer

Calculates the texture coordinates for \a area using the texture size \a size.

\param area The portion of the texture to calculate the coordinates for

\param size The size of the texture

\tparam Ret The floating point type for the resulting rect to use

\return The texture coordinates in [(0,0),(1,1)]

\warning The behaviour is undefined if \a area lies outside of \a size
*/
template<
	typename Ret
>
SGE_RENDERER_DETAIL_SYMBOL
typename boost::enable_if<
	fcppt::type_traits::is_float_or_double<
		Ret
	>,
	fcppt::math::box::rect<
		Ret
	>
>::type const
lock_rect_to_coords(
	sge::renderer::lock_rect const &area,
	sge::renderer::dim2 const &size
);

}
}

#endif
