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
#include <sge/libpng/from_sge_format_exn.hpp>
#include <sge/libpng/to_sge_format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::libpng::file_rep
sge::libpng::file_rep_from_view(
	sge::image2d::view::const_object const &_view
)
{
	sge::image2d::dim const size(
		sge::image2d::view::size(
			_view
		)
	);

	sge::libpng::format const png_dest_format(
		sge::libpng::from_sge_format_exn(
			sge::image2d::view::format(
				_view
			)
		)
	);

	sge::image::color::format const dest_format(
		sge::libpng::to_sge_format(
			png_dest_format
		)
	);

	sge::libpng::byte_vector bytes(
		size.content()
		*
		sge::image::color::format_stride(
			dest_format
		)
	);

	sge::image2d::algorithm::copy_and_convert(
		_view,
		sge::image2d::view::make(
			bytes.data(),
			size,
			dest_format,
			sge::image2d::pitch::null()
		),
		sge::image::algorithm::may_overlap::no,
		sge::image::algorithm::uninitialized::yes
	);

	return
		sge::libpng::file_rep(
			size,
			png_dest_format,
			std::move(
				bytes
			)
		);
}
