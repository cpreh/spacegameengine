/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/exception.hpp>
#include <sge/image/file_exception.hpp>
#include <sge/image/optional_path.hpp>
#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/libpng/check_extension.hpp>
#include <sge/libpng/file.hpp>
#include <sge/libpng/extension.hpp>
#include <sge/libpng/is_png.hpp>
#include <sge/libpng/system.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/array.hpp>
#include <ios>
#include <fcppt/config/external_end.hpp>


sge::libpng::system::system()
{
}

sge::libpng::system::~system()
{
}

sge::image2d::optional_file_unique_ptr
sge::libpng::system::load(
	boost::filesystem::path const &_path
)
{
	boost::filesystem::ifstream file_stream(
		_path,
		std::ios_base::binary
	);

	if(
		!file_stream.is_open()
	)
		throw
			sge::image::exception{
				FCPPT_TEXT("Couldn't open ")
				+
				fcppt::filesystem::path_to_string(
					_path
				)
			};

	return
		this->load_impl(
			file_stream,
			sge::image::optional_path(
				_path
			)
		);
}

sge::image2d::optional_file_unique_ptr
sge::libpng::system::load_raw(
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	if(
		!sge::libpng::check_extension(
			_extension
		)
	)
		return
			sge::image2d::optional_file_unique_ptr();

	typedef
	boost::iostreams::stream<
		boost::iostreams::array_source
	>
	stream_type;

	stream_type raw_stream(
		fcppt::cast::to_char_ptr<
			boost::iostreams::array_source::char_type const *
		>(
			_range.begin()
		),
		fcppt::cast::to_char_ptr<
			boost::iostreams::array_source::char_type const *
		>(
			_range.end()
		)
	);

	return
		this->load_impl(
			raw_stream,
			sge::image::optional_path()
		);
}

sge::image2d::optional_file_unique_ptr
sge::libpng::system::load_stream(
	std::istream &_stream,
	sge::media::optional_extension const &_extension
)
{
	return
		sge::libpng::check_extension(
			_extension
		)
		?
			this->load_impl(
				_stream,
				sge::image::optional_path()
			)
		:
			sge::image2d::optional_file_unique_ptr()
		;
}

sge::image2d::optional_file_unique_ptr
sge::libpng::system::create(
	sge::image2d::view::const_object const &_view,
	sge::media::optional_extension const &_extension
)
{
	return
		sge::libpng::check_extension(
			_extension
		)
		?
			sge::image2d::optional_file_unique_ptr(
				fcppt::make_unique_ptr<
					file
				>(
					_view
				)
			)
		:
			sge::image2d::optional_file_unique_ptr()
		;
}

sge::media::extension_set
sge::libpng::system::extensions() const
{
	return
		sge::media::extension_set{
			sge::libpng::extension()
		};
}

sge::image2d::optional_file_unique_ptr
sge::libpng::system::load_impl(
	std::istream &_stream,
	sge::image::optional_path const &_path
)
{
	// Handle the most common "error" without exceptions
	return
		sge::libpng::is_png(
			_stream
		)
		?
			sge::image2d::optional_file_unique_ptr(
				fcppt::make_unique_ptr<
					sge::libpng::file
				>(
					_stream,
					_path
				)
			)
		:
			sge::image2d::optional_file_unique_ptr()
		;
}
