//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
