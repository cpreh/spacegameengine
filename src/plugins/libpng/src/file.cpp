/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../load_context.hpp"
#include "../write_context.hpp"
#include <sge/image/view/dim.hpp>
#include <sge/image/view/format.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/color/format_stride.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/optional_impl.hpp>

sge::libpng::file::file(
	fcppt::filesystem::path const &_path)
{
	load_context context(
		_path);
	dim_ = context.dim();

	bytes_.swap(
		context.bytes());
	format_ = context.format();
}

sge::libpng::file::file(
	image::view::const_object const &_view)
{
	data(
		_view);
}

void sge::libpng::file::data(
	image::view::const_object const &_view)
{
	dim_ =
		image::view::dim(
			_view);

	format_ =
		image::view::format(
			_view);

	bytes_.resize(
		dim_.content() *
		image::color::format_stride(
			format_));

	image::algorithm::copy_and_convert(
		_view,
		image::view::make(
			bytes_.data(),
			dim_,
			format_,
			image::view::optional_pitch()));
}

sge::image::view::const_object const sge::libpng::file::view() const
{
	return
		image::view::make(
			reinterpret_cast<image::const_raw_pointer>(
				bytes_.data()),
			dim(),
			format_,
			image::view::optional_pitch());
}

sge::image::dim_type const sge::libpng::file::dim() const
{
	return dim_;
}

void sge::libpng::file::save(
	fcppt::filesystem::path const &p)
{
	write_context context(
		p,
		dim(),
		bytes_,
		format_);
}
