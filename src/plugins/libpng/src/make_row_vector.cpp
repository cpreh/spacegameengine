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
#include <sge/image2d/dim.hpp>
#include <sge/libpng/bytes_per_pixel.hpp>
#include <sge/libpng/make_row_vector.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/row_vector.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/algorithm/map.hpp>


sge::libpng::row_vector
sge::libpng::make_row_vector(
	sge::image2d::dim const _size,
	png_bytep const _data,
	sge::libpng::bytes_per_pixel const _bytes_per_pixel
)
{
	sge::image::size_type const stride(
		_bytes_per_pixel.get()
		*
		_size.w()
	);

	return
		fcppt::algorithm::map<
			sge::libpng::row_vector
		>(
			fcppt::make_int_range_count(
				_size.h()
			),
			[
				_data,
				stride
			](
				sge::image::size_type const _index
			)
			{
				return
					_data
					+
					_index
					*
					stride;
			}
		);
}
