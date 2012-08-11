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


#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/unsupported_format.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/libpng/file.hpp>
#include <sge/libpng/is_png.hpp>
#include <sge/libpng/load_context.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/write_context.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::libpng::file::file(
	std::istream &_stream,
	sge::image::optional_path const &_path
)
:
	dim_(),
	format_(),
	bytes_()
{
	if(
		!libpng::is_png(
			_stream
		)
	)
		throw
			image::unsupported_format(
				_path,
				FCPPT_TEXT("not a png file")
			);

	libpng::load_context context(
		_stream,
		_path
	);

	dim_ = context.dim();

	bytes_.swap(
		context.bytes()
	);

	format_ = context.format();
}

sge::libpng::file::file(
	image2d::view::const_object const &_view
)
:
	dim_(
		image2d::view::size(
			_view
		)
	),
	format_(
		image2d::view::format(
			_view
		)
	),
	bytes_(
		dim_.content() *
		image::color::format_stride(
			format_
		)
	)
{
	image2d::algorithm::copy_and_convert(
		_view,
		image2d::view::make(
			bytes_.data(),
			dim_,
			format_,
			sge::image2d::pitch::null()
		),
		sge::image::algorithm::may_overlap::no
	);
}

sge::libpng::file::~file()
{
}

sge::image2d::view::const_object const
sge::libpng::file::view() const
{
	return
		image2d::view::make_const(
			reinterpret_cast<
				image::const_raw_pointer
			>(
				bytes_.data()
			),
			this->size(),
			format_,
			sge::image2d::pitch::null()
		);
}

sge::image2d::dim const
sge::libpng::file::size() const
{
	return dim_;
}

void
sge::libpng::file::save(
	boost::filesystem::path const &_path
) const
{
	libpng::write_context context(
		_path,
		this->size(),
		bytes_,
		format_
	);
}
