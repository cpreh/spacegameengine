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


#ifndef SGE_D3D9_FROM_D3D_PITCH_HPP_INCLUDED
#define SGE_D3D9_FROM_D3D_PITCH_HPP_INCLUDED

#include <sge/image/basic_dim.hpp>
#include <sge/image/basic_pitch.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/math/at_c.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/init.hpp>
#include <fcppt/math/dim/narrow_cast.hpp>


namespace sge
{
namespace d3d9
{

template<
	sge::image::size_type Dim
>
sge::image::basic_pitch<
	Dim
>
from_d3d_pitch(
	sge::image::basic_pitch<
		Dim
	> const &_pitches,
	sge::image::basic_dim<
		Dim
	> const &_dim,
	sge::image::color::format const _format
)
{
	return
		fcppt::math::dim::init<
			sge::image::basic_pitch<
				Dim
			>
		>(
			[
				&_pitches,
				&_dim,
				_format
			](
				auto const _index
			)
			{
				return
					fcppt::math::at_c<
						_index
					>(
						_pitches
					)
					-
					fcppt::cast::to_signed(
						fcppt::math::dim::contents(
							fcppt::math::dim::narrow_cast<
								sge::image::basic_dim<
									Dim
									-
									1
								>
							>(
								_dim
							)
						)
						*
						sge::image::color::format_stride(
							_format
						)
					);
			}
		);
}

}
}

#endif
