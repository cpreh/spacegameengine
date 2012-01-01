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


#ifndef SGE_D3D9_FROM_D3D_PITCH_HPP_INCLUDED
#define SGE_D3D9_FROM_D3D_PITCH_HPP_INCLUDED

#include <sge/image/dim.hpp>
#include <sge/image/pitch.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/narrow_cast.hpp>


namespace sge
{
namespace d3d9
{

template<
	sge::image::size_type Dim
>
fcppt::optional<
	typename sge::image::pitch<
		Dim
	>::type
> const
from_d3d_pitch(
	typename sge::image::pitch<
		Dim
	>::type const &_pitches,
	typename sge::image::dim<
		Dim
	>::type const &_dim,
	sge::image::color::format::type const _format
)
{
	typedef typename sge::image::pitch<
		Dim
	>::type dest_type;

	typedef fcppt::optional<
		dest_type
	> result_type;

	dest_type dest;

	for(
		typename dest_type::size_type index = 0;
		index < dest_type::dim_wrapper::value;
		++index
	)
		dest[index] =
			_pitches[index]
			-
			static_cast<
				typename dest_type::value_type
			>(
				fcppt::math::dim::narrow_cast<
					typename sge::image::dim<
						Dim - 1
					>::type
				>(
					_dim
				).content()
				*
				sge::image::color::format_stride(
					_format
				)
			);

	return
		dest.content()
		?
			result_type()
		:
			result_type(
				dest
			);
}

}
}

#endif
