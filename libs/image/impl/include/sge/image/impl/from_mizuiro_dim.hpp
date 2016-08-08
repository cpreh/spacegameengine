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


#ifndef SGE_IMAGE_IMPL_FROM_MIZUIRO_DIM_HPP_INCLUDED
#define SGE_IMAGE_IMPL_FROM_MIZUIRO_DIM_HPP_INCLUDED

#include <mizuiro/size_type.hpp>
#include <mizuiro/image/dimension.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/init.hpp>
#include <fcppt/math/dim/static.hpp>


namespace sge
{
namespace image
{
namespace impl
{

template<
	typename T,
	mizuiro::size_type N
>
fcppt::math::dim::static_<
	T,
	N
>
from_mizuiro_dim(
	mizuiro::image::dimension<
		N,
		T
	> const &_src
)
{
	return
		fcppt::math::dim::init<
			fcppt::math::dim::static_<
				T,
				N
			>
		>(
			[
				&_src
			](
				fcppt::math::size_type const _index
			)
			{
				return
					_src[
						_index
					];
			}
		);
}

}
}
}

#endif
