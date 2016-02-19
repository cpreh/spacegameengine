/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SRC_CEGUI_FROM_CEGUI_RECT_HPP_INCLUDED
#define SGE_SRC_CEGUI_FROM_CEGUI_RECT_HPP_INCLUDED

#include <fcppt/math/box/has_dim.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Rect.h>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cegui
{

template<
	typename Container,
	typename ValueType
>
typename
boost::enable_if
<
	fcppt::math::box::has_dim
	<
		Container,
		2u
	>,
	Container
>::type
from_cegui_rect(
	CEGUI::Rect<
		ValueType
	> const &_rect
)
{
	// When we need Vector conversion functions, use them instead!
	return
		Container(
			typename Container::vector(
				static_cast<
					typename Container::vector::value_type
				>(
					_rect.left()
				),
				static_cast<
					typename Container::vector::value_type
				>(
					_rect.top()
				)
			),
			typename Container::dim(
				static_cast<
					typename Container::dim::value_type
				>(
					_rect.getWidth()
				),
				static_cast<
					typename Container::dim::value_type
				>(
					_rect.getHeight()
				)
			)
		);
}

}
}

#endif
