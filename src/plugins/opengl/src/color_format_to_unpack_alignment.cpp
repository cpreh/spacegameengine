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
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/opengl/color_format_to_unpack_alignment.hpp>
#include <sge/opengl/unpack_alignment.hpp>


sge::opengl::unpack_alignment const
sge::opengl::color_format_to_unpack_alignment(
	sge::image::color::format::type const _format
)
{
	sge::image::size_type const stride(
		sge::image::color::format_stride(
			_format
		)
	);

	if(
		(stride % 8u) == 0u
	)
		return
			sge::opengl::unpack_alignment(
				8
			);

	if(
		(stride % 4u) == 0u
	)
		return
			sge::opengl::unpack_alignment(
				4
			);

	if(
		(stride % 2u) == 0u
	)
		return
			sge::opengl::unpack_alignment(
				2
			);

	return
		sge::opengl::unpack_alignment(
			1
		);
}
