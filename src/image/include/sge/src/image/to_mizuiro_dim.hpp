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


#ifndef SGE_SRC_IMAGE_TO_MIZUIRO_DIM_HPP_INCLUDED
#define SGE_SRC_IMAGE_TO_MIZUIRO_DIM_HPP_INCLUDED

#include <mizuiro/image/dimension.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{

template<
	typename T,
	fcppt::math::size_type N,
	typename S
>
mizuiro::image::dimension<
	N,
	T
>
to_mizuiro_dim(
	fcppt::math::dim::object<
		T,
		N,
		S
	> const &_src
)
{
	// TODO: Use proper initialization here
	mizuiro::image::dimension<
		N,
		T
	> dest;

	std::copy(
		_src.storage().begin(),
		_src.storage().end(),
		dest.begin()
	);

	return
		dest;
}

}
}

#endif
