/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../file.hpp"
#include "../is_png.hpp"
#include "../load_context.hpp"
#include "../png.hpp"
#include "../write_context.hpp"
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/unsupported_format.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/size.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


sge::libpng::file::file(
	std::istream &_stream,
	sge::image::optional_path const &_path
)
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
{
	data(
		_view
	);
}

sge::libpng::file::~file()
{
}

void
sge::libpng::file::data(
	image2d::view::const_object const &_view
)
{
	dim_ =
		image2d::view::size(
			_view
		);

	format_ =
		image2d::view::format(
			_view
		);

	bytes_.resize(
		dim_.content() *
		image::color::format_stride(
			format_
		)
	);

	image2d::algorithm::copy_and_convert(
		_view,
		image2d::view::make(
			bytes_.data(),
			dim_,
			format_,
			image2d::view::optional_pitch()
		),
		sge::image::algorithm::may_overlap::no
	);
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
			image2d::view::optional_pitch()
		);
}

sge::image2d::dim const
sge::libpng::file::size() const
{
	return dim_;
}

void
sge::libpng::file::save(
	fcppt::filesystem::path const &_path
)
{
	write_context context(
		_path,
		this->size(),
		bytes_,
		format_
	);
}
