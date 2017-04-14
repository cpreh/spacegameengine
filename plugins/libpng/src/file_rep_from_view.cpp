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


#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/libpng/byte_vector.hpp>
#include <sge/libpng/file_rep.hpp>
#include <sge/libpng/file_rep_from_view.hpp>
#include <sge/libpng/format.hpp>
#include <sge/libpng/from_sge_format.hpp>
#include <sge/libpng/optional_file_rep.hpp>
#include <sge/libpng/to_sge_format.hpp>
#include <fcppt/container/buffer/read_from.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::libpng::optional_file_rep
sge::libpng::file_rep_from_view(
	sge::image2d::view::const_object const &_view
)
{
	return
		fcppt::optional::map(
			sge::libpng::from_sge_format(
				sge::image2d::view::format(
					_view
				)
			),
			[
				&_view
			](
				sge::libpng::format const _png_dest_format
			)
			{
				sge::image2d::dim const size(
					sge::image2d::view::size(
						_view
					)
				);

				sge::image::color::format const dest_format(
					sge::libpng::to_sge_format(
						_png_dest_format
					)
				);

				sge::libpng::byte_vector bytes{
					fcppt::container::buffer::to_raw_vector(
						fcppt::container::buffer::read_from<
							sge::libpng::byte_vector::value_type
						>(
							fcppt::math::dim::contents(
								size
							)
							*
							sge::image::color::format_stride(
								dest_format
							),
							[
								size,
								dest_format,
								&_view
							](
								sge::libpng::byte_vector::pointer const _data,
								sge::libpng::byte_vector::size_type const _byte_size
							)
							{
								sge::image2d::algorithm::copy_and_convert(
									_view,
									sge::image2d::view::make(
										_data,
										size,
										dest_format,
										fcppt::math::dim::null<
											sge::image2d::pitch
										>()
									),
									sge::image::algorithm::may_overlap::no,
									sge::image::algorithm::uninitialized::yes
								);

								return
									_byte_size;
							}
						)
					)
				};

				return
					sge::libpng::file_rep(
						size,
						_png_dest_format,
						std::move(
							bytes
						)
					);
			}
		);
}
