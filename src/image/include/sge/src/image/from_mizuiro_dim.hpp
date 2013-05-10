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


#ifndef SGE_SRC_IMAGE_FROM_MIZUIRO_DIM_HPP_INCLUDED
#define SGE_SRC_IMAGE_FROM_MIZUIRO_DIM_HPP_INCLUDED

#include <mizuiro/size_type.hpp>
#include <mizuiro/image/dimension.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{

template<
	typename Dest,
	typename T,
	mizuiro::size_type N
>
Dest const
from_mizuiro_dim(
	mizuiro::image::dimension<
		N,
		T
	> const &_src
)
{
	static_assert(
		std::is_same<
			typename Dest::value_type,
			T
		>::value,
		"The value types must be the same"
	);

	static_assert(
		Dest::dim_wrapper::value
		==
		N,
		"The dimensions must be the same"
	);

	Dest dest{
		fcppt::no_init()
	};

	std::copy(
		_src.begin(),
		_src.end(),
		dest.begin()
	);

	return dest;
}

}
}

#endif
