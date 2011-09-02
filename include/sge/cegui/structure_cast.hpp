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


#ifndef SGE_CEGUI_STRUCTURE_CAST_HPP_INCLUDED
#define SGE_CEGUI_STRUCTURE_CAST_HPP_INCLUDED

#include <sge/cegui/unit.hpp>
#include <fcppt/math/vector/has_dim.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/has_dim.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/box/has_dim.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUISize.h>
#include <CEGUIRect.h>
#include <CEGUIVector.h>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace cegui
{
template<typename Container>
typename
boost::enable_if_c
<
	fcppt::math::vector::has_dim<Container,static_cast<fcppt::math::size_type>(2)>::value ||
	fcppt::math::dim::has_dim<Container,static_cast<fcppt::math::size_type>(2)>::value,
	CEGUI::Size
>::type
structure_cast(
	Container const &c)
{
	return
		CEGUI::Size(
			static_cast<unit>(c[0]),
			static_cast<unit>(c[1]));
}

template<typename Container>
typename
boost::enable_if_c
<
	fcppt::math::vector::has_dim<Container,static_cast<fcppt::math::size_type>(2)>::value ||
	fcppt::math::dim::has_dim<Container,static_cast<fcppt::math::size_type>(2)>::value,
	Container
>::type
structure_cast(
	CEGUI::Size const &s)
{
	return
		Container(
			static_cast<typename Container::value_type>(
				s.d_width),
			static_cast<typename Container::value_type>(
				s.d_height));
}







template<typename Container>
typename
boost::enable_if_c
<
	fcppt::math::box::has_dim<Container,static_cast<fcppt::math::size_type>(2)>::value,
	CEGUI::Rect
>::type
structure_cast(
	Container const &c)
{
	return
		CEGUI::Rect(
			static_cast<unit>(
				c.left()),
			static_cast<unit>(
				c.top()),
			static_cast<unit>(
				c.right()),
			static_cast<unit>(
				c.bottom()));
}

template<typename Container>
typename
boost::enable_if_c
<
	fcppt::math::box::has_dim<Container,static_cast<fcppt::math::size_type>(2)>::value,
	Container
>::type
structure_cast(
	CEGUI::Rect const &s)
{
	return
		Container(
			typename Container::vector(
				static_cast<typename Container::vector::value_type>(
					s.d_left),
				static_cast<typename Container::vector::value_type>(
					s.d_top)),
			typename Container::dim(
				static_cast<typename Container::dim::value_type>(
					s.d_right - s.d_left),
				static_cast<typename Container::dim::value_type>(
					s.d_bottom - s.d_top)));
}
}
}

#endif
