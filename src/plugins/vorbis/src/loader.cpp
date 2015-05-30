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


#include <sge/audio/file.hpp>
#include <sge/audio/file_exception.hpp>
#include <sge/audio/optional_file_unique_ptr.hpp>
#include <sge/audio/unsupported_format.hpp>
#include <sge/media/check_extension.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/media/optional_path.hpp>
#include <sge/vorbis/file.hpp>
#include <sge/vorbis/loader.hpp>
#include <sge/vorbis/stream_ptr.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/io/raw_container_source.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/iostreams/stream.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::media::extension const extension(
	FCPPT_TEXT("ogg")
);

bool
check_extension(
	sge::media::optional_extension const &_extension
)
{
	return
		sge::media::check_extension(
			extension,
			_extension
		);
}

}

sge::vorbis::loader::loader()
{
}

sge::vorbis::loader::~loader()
{
}

sge::audio::optional_file_unique_ptr
sge::vorbis::loader::load(
	boost::filesystem::path const &filename
)
{
	stream_ptr file_stream(
		fcppt::unique_ptr_to_base<
			std::istream
		>(
			fcppt::make_unique_ptr_fcppt<
				boost::filesystem::ifstream
			>(
				filename,
				std::ios::binary
			)
		)
	);

	// TODO: Remove the static_cast here
	if(!static_cast<boost::filesystem::ifstream &>(*file_stream).is_open())
		throw audio::file_exception(
			sge::media::optional_path(
				filename),
			FCPPT_TEXT("couldn't open file"));
	try
	{
		return
			sge::audio::optional_file_unique_ptr(
				fcppt::unique_ptr_to_base<
					sge::audio::file
				>(
					fcppt::make_unique_ptr_fcppt<
						sge::vorbis::file
					>(
						std::move(
							file_stream
						),
						sge::media::optional_path(
							filename
						)
					)
				)
			);
	}
	catch(
		sge::audio::unsupported_format const &
	)
	{
		return
			sge::audio::optional_file_unique_ptr();
	}
}

sge::audio::optional_file_unique_ptr
sge::vorbis::loader::load_raw(
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	if(
		!check_extension(
			_extension
		)
	)
		return
			sge::audio::optional_file_unique_ptr();

	typedef
	boost::iostreams::stream
	<
		fcppt::io::raw_container_source
		<
			fcppt::container::raw_vector<char>
		>
	>
	stream_type;

	stream_ptr raw_stream(
		fcppt::unique_ptr_to_base<
			std::istream
		>(
			fcppt::make_unique_ptr_fcppt<stream_type>(
				reinterpret_cast<boost::iostreams::array_source::char_type const *>(
					_range.begin()),
				reinterpret_cast<boost::iostreams::array_source::char_type const *>(
					_range.end()
				)
			)
		)
	);

	try
	{
		return
			sge::audio::optional_file_unique_ptr(
				fcppt::unique_ptr_to_base<
					sge::audio::file
				>(
					fcppt::make_unique_ptr_fcppt<
						sge::vorbis::file
					>(
						std::move(
							raw_stream
						),
						sge::media::optional_path()
					)
				)
			);
	}
	catch(
		sge::audio::unsupported_format const &
	)
	{
		return
			sge::audio::optional_file_unique_ptr();
	}
}

sge::audio::optional_file_unique_ptr
sge::vorbis::loader::load_stream(
	std::istream &_stream,
	sge::media::optional_extension const &_extension
)
{
	if(
		!check_extension(
			_extension
		)
	)
		return
			sge::audio::optional_file_unique_ptr();

	try
	{
		return
			sge::audio::optional_file_unique_ptr(
				fcppt::unique_ptr_to_base<
					sge::audio::file
				>(
					fcppt::make_unique_ptr_fcppt<
						sge::vorbis::file
					>(
						// This is supposed to create a new istream which
						// replaces the old one. I'm not sure if rdbuf(0)
						// is allowed and if this is the best way to
						// achieve the goal.
						fcppt::make_unique_ptr_fcppt<
							std::istream
						>(
							_stream.rdbuf(
								nullptr
							)
						),
						sge::media::optional_path()
					)
				)
			);
	}
	catch(
		audio::unsupported_format const &
	)
	{
		return
			sge::audio::optional_file_unique_ptr();
	}
}

sge::media::extension_set
sge::vorbis::loader::extensions() const
{
	return
		sge::media::extension_set{
			extension
		};
}
