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


#include <sge/image/size_type.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/stride_to_unpack_alignment.hpp>
#include <sge/opengl/unpack_alignment.hpp>


sge::opengl::unpack_alignment const
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
				static_cast<
					GLint
				>(
					_stride
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
