/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_CEGUI_TO_CEGUI_VECTOR2_HPP_INCLUDED
#define SGE_SRC_CEGUI_TO_CEGUI_VECTOR2_HPP_INCLUDED

#include <fcppt/math/size_type.hpp>
#include <fcppt/math/vector/has_dim.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Vector.h>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cegui
{

template<
	typename ValueType,
	typename Container
>
typename
boost::enable_if
<
	fcppt::math::vector::has_dim<
		Container,
		2u
	>,
	CEGUI::Vector2<
		ValueType
	>
>::type
to_cegui_vector2(
	Container const &_container
)
{
	return
		CEGUI::Vector2<
			ValueType
		>(
			static_cast<
				ValueType
			>(
				_container[0]
			),
			static_cast<
				ValueType
			>(
				_container[1]
			)
		);
}

}
}

#endif
