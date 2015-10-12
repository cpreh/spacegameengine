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


#include <sge/image/size_type.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/stride_to_unpack_alignment.hpp>
#include <sge/opengl/unpack_alignment.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>


sge::opengl::unpack_alignment
sge::opengl::stride_to_unpack_alignment(
	sge::image::size_type const _stride
)
{
	for(
		GLint divisor(
			8
		);
		divisor != 1;
		divisor /= 2
	)

		if(
			(
				fcppt::cast::size<
					GLint
				>(
					fcppt::cast::to_signed(
						_stride
					)
				)
				%
				divisor
			)
			== 0
		)
			return
				sge::opengl::unpack_alignment(
					divisor
				);

	return
		sge::opengl::unpack_alignment(
			1
		);
}
