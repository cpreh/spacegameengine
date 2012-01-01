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


#include <sge/devil/best_il_format.hpp>
#include <sge/devil/check_error_exn.hpp>
#include <sge/devil/convert_format.hpp>
#include <sge/devil/disable.hpp>
#include <sge/devil/enable.hpp>
#include <sge/devil/file.hpp>
#include <sge/devil/get_data.hpp>
#include <sge/devil/get_integer.hpp>
#include <sge/devil/load_image.hpp>
#include <sge/devil/load_memory.hpp>
#include <sge/devil/set_integer.hpp>
#include <sge/devil/to_il_channel.hpp>
#include <sge/devil/to_il_format.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/exception.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/element_count.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/log/global.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/assert/post.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <IL/il.h>
#include <fcppt/config/external_end.hpp>


sge::devil::file::file()
:
	impl_()
{
}

sge::devil::file::file(
	image2d::view::const_object const &_src
)
:
	impl_()
{
	this->bind();

	typedef fcppt::container::raw_vector<
		unsigned char
	> raw_vector;

	image2d::dim const src_dim(
		image2d::view::size(
			_src
		)
	);

	image::color::format::type const fmt(
		image2d::view::format(
			_src
		)
	);

	raw_vector temp(
		image::color::format_stride(fmt)
		* src_dim.content()
	);

	image::color::format::type const best_il_format(
		devil::best_il_format(
			fmt
		)
	);

	image2d::algorithm::copy_and_convert(
		_src,
		image2d::view::make(
			temp.data(),
			src_dim,
			best_il_format,
			image2d::view::optional_pitch()
		),
		sge::image::algorithm::may_overlap::no
	);

	image2d::dim const cur_dim(
		image2d::view::size(
			_src
		)
	);

	::ilTexImage(
		static_cast<
			ILuint
		>(
			cur_dim.w()
		),
		static_cast<
			ILuint
		>(
			cur_dim.h()
		),
		1,
		static_cast<
			ILubyte
		>(
			sge::image::color::element_count(
				best_il_format
			)
		),
		devil::to_il_format(
			best_il_format
		),
		devil::to_il_channel(
			best_il_format
		),
		const_cast<
			raw_vector::pointer
		>(
			temp.data()
		)
	);

	devil::check_error_exn();
}

sge::devil::file::~file()
{
}

sge::image2d::dim const
sge::devil::file::size() const
{
	this->bind();

	return
		image2d::dim(
			static_cast<
				image2d::dim::value_type
			>(
				devil::get_integer(
					IL_IMAGE_WIDTH
				)
			),
			static_cast<
				image2d::dim::value_type
			>(
				devil::get_integer(
					IL_IMAGE_HEIGHT
				)
			)
		);
}

sge::image2d::view::const_object const
sge::devil::file::view() const
{
	this->bind();

	return
		image2d::view::make_const(
			const_cast<
				image::const_raw_pointer
			>(
				devil::get_data()
			),
			this->size(),
			devil::convert_format(
				devil::get_integer(
					IL_IMAGE_BITS_PER_PIXEL
				),
				this->format()
			),
			image2d::view::optional_pitch()
		);
}

void
sge::devil::file::save(
	fcppt::filesystem::path const &_file
) const
{
	this->bind();

	devil::enable(
		IL_ORIGIN_SET
	);

	::ilRegisterOrigin(
		IL_ORIGIN_UPPER_LEFT
	);

	devil::check_error_exn();

	::ilSaveImage(
#ifdef UNICODE
		const_cast<
			wchar_t *
		>(
			fcppt::filesystem::path_to_string(
				_file
			).c_str()
		)
#else
		const_cast<
			char *
		>(
			fcppt::to_std_string(
				fcppt::filesystem::path_to_string(
					_file
				)
			).c_str()
		)
#endif
	);

	devil::check_error_exn();

	devil::disable(
		IL_ORIGIN_SET
	);
}

void
sge::devil::file::bind() const
{
	::ilBindImage(
		impl_.id()
	);

	devil::check_error_exn();
}

sge::devil::optional_error const
sge::devil::file::load(
	fcppt::filesystem::path const &_file
)
{
	return
		this->load_impl(
			std::tr1::bind(
				devil::load_image,
				_file
			)
		);
}

sge::devil::optional_error const
sge::devil::file::load(
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	return
		this->load_impl(
			std::tr1::bind(
				devil::load_memory,
				_range,
				_extension
			)
		);

}

sge::devil::optional_error const
sge::devil::file::load_impl(
	load_function const &_function
)
{
	this->bind();

	devil::disable(
		IL_FORMAT_SET
	);

	{
		devil::optional_error const error(
			_function()
		);

		if(
			error
			|| this->format() != IL_COLOR_INDEX
		)
			return error;
	}

	FCPPT_LOG_WARNING(
		sge::log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("SGE won't handle files with color palettes.")
			<< FCPPT_TEXT(" Instead, the file will be reloaded and converted.")
			<< FCPPT_TEXT(" The process is inefficient and you should consider ")
			<< FCPPT_TEXT(" converting the file beforehand.")
	);

	devil::set_integer(
		IL_FORMAT_MODE,
		IL_RGBA
	);

	devil::enable(
		IL_FORMAT_SET
	);

	devil::optional_error const error(
		_function()
	);

	FCPPT_ASSERT_POST(
		this->format() != IL_COLOR_INDEX,
		sge::image::exception
	);

	return error;
}

ILenum
sge::devil::file::format() const
{
	this->bind();

	return
		static_cast<
			ILenum
		>(
			devil::get_integer(
				IL_IMAGE_FORMAT
			)
		);
}
