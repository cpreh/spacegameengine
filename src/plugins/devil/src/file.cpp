/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/devil/logger.hpp>
#include <sge/devil/set_integer.hpp>
#include <sge/devil/to_il_channel.hpp>
#include <sge/devil/to_il_format.hpp>
#include <sge/image/const_raw_pointer.hpp>
#include <sge/image/exception.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/color/element_count.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/assert/post.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/io/stream_to_string.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <IL/il.h>
#include <boost/filesystem/path.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::devil::file::file()
:
	impl_()
{
}

sge::devil::file::file(
	sge::image2d::view::const_object const &_src
)
:
	impl_()
{
	this->bind();

	typedef fcppt::container::raw_vector<
		unsigned char
	> raw_vector;

	sge::image2d::dim const src_dim(
		sge::image2d::view::size(
			_src
		)
	);

	image::color::format const fmt(
		image2d::view::format(
			_src
		)
	);

	raw_vector temp(
		sge::image::color::format_stride(
			fmt
		)
		* src_dim.content()
	);

	sge::image::color::format const best_il_format(
		devil::best_il_format(
			fmt
		)
	);

	sge::image2d::algorithm::copy_and_convert(
		_src,
		sge::image2d::view::make(
			temp.data(),
			src_dim,
			best_il_format,
			sge::image2d::pitch::null()
		),
		sge::image::algorithm::may_overlap::no
	);

	sge::image2d::dim const cur_dim(
		sge::image2d::view::size(
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
		sge::devil::to_il_format(
			best_il_format
		),
		sge::devil::to_il_channel(
			best_il_format
		),
		const_cast<
			raw_vector::pointer
		>(
			temp.data()
		)
	);

	sge::devil::check_error_exn();
}

sge::devil::file::~file()
{
}

sge::image2d::dim const
sge::devil::file::size() const
{
	this->bind();

	return
		sge::image2d::dim(
			static_cast<
				sge::image2d::dim::value_type
			>(
				sge::devil::get_integer(
					IL_IMAGE_WIDTH
				)
			),
			static_cast<
				sge::image2d::dim::value_type
			>(
				sge::devil::get_integer(
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
		sge::image2d::view::make_const(
			const_cast<
				sge::image::const_raw_pointer
			>(
				devil::get_data()
			),
			this->size(),
			sge::devil::convert_format(
				sge::devil::get_integer(
					IL_IMAGE_BITS_PER_PIXEL
				),
				this->format()
			),
			sge::image2d::pitch::null()
		);
}

void
sge::devil::file::save(
	boost::filesystem::path const &_file
) const
{
	this->bind();

	sge::devil::enable(
		IL_ORIGIN_SET
	);

	::ilRegisterOrigin(
		IL_ORIGIN_UPPER_LEFT
	);

	sge::devil::check_error_exn();

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

	sge::devil::check_error_exn();

	sge::devil::disable(
		IL_ORIGIN_SET
	);
}

void
sge::devil::file::bind() const
{
	::ilBindImage(
		impl_.id()
	);

	sge::devil::check_error_exn();
}

sge::devil::optional_error const
sge::devil::file::load(
	boost::filesystem::path const &_file
)
{
	return
		this->load_impl(
			std::bind(
				sge::devil::load_image,
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
			std::bind(
				sge::devil::load_memory,
				_range,
				_extension
			)
		);

}

sge::devil::optional_error const
sge::devil::file::load(
	std::istream &_stream,
	sge::media::optional_extension const &_extension
)
{
	std::string const content(
		fcppt::io::stream_to_string(
			_stream
		)
	);

	return
		this->load_impl(
			std::bind(
				sge::devil::load_memory,
				boost::make_iterator_range(
					reinterpret_cast<
						sge::media::const_raw_pointer
					>(
						&(*content.begin())
					),
					reinterpret_cast<
						sge::media::const_raw_pointer
					>(
						&(*content.end())
					)
				),
				_extension
			)
		);

}

sge::devil::optional_error const
sge::devil::file::load_impl(
	sge::devil::file::load_function const &_function
)
{
	this->bind();

	sge::devil::disable(
		IL_FORMAT_SET
	);

	{
		sge::devil::optional_error const error(
			_function()
		);

		if(
			error
			|| this->format() != IL_COLOR_INDEX
		)
			return error;
	}

	FCPPT_LOG_WARNING(
		sge::devil::logger(),
		fcppt::log::_
			<< FCPPT_TEXT("SGE won't handle files with color palettes.")
			<< FCPPT_TEXT(" Instead, the file will be reloaded and converted.")
			<< FCPPT_TEXT(" The process is inefficient and you should consider ")
			<< FCPPT_TEXT(" converting the file beforehand.")
	);

	sge::devil::set_integer(
		IL_FORMAT_MODE,
		IL_RGBA
	);

	sge::devil::enable(
		IL_FORMAT_SET
	);

	sge::devil::optional_error const error(
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
			sge::devil::get_integer(
				IL_IMAGE_FORMAT
			)
		);
}
