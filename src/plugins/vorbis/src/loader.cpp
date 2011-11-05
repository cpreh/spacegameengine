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


#include <sge/vorbis/file.hpp>
#include <sge/vorbis/loader.hpp>
#include <sge/vorbis/stream_ptr.hpp>
#include <sge/extension_set.hpp>
#include <sge/audio/file_exception.hpp>
#include <sge/audio/optional_path.hpp>
#include <sge/audio/unsupported_format.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/move.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/io/raw_container_source.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/stream.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{
sge::extension_set const extensions_(
	fcppt::assign::make_container<sge::extension_set>(
		FCPPT_TEXT("ogg")));
}

sge::vorbis::loader::loader()
{
}

sge::vorbis::loader::~loader()
{
}

sge::audio::file_ptr const
sge::vorbis::loader::load(
	fcppt::filesystem::path const &filename
)
{
	stream_ptr file_stream(
		fcppt::make_unique_ptr<fcppt::io::cifstream>(
			filename,
			std::ios::binary));
	if(!static_cast<fcppt::io::cifstream &>(*file_stream).is_open())
		throw audio::file_exception(
			sge::audio::optional_path(
				filename),
			FCPPT_TEXT("couldn't open file"));
	try
	{
		return
			// Can't use make_shared here because of the unique_ptr
			sge::audio::file_ptr(
				new vorbis::file(
					fcppt::move(
						file_stream),
					sge::audio::optional_path(
						filename)));
	}
	catch (audio::unsupported_format const &)
	{
		return sge::audio::file_ptr();
	}
}

sge::audio::file_ptr const
sge::vorbis::loader::load_raw(
	sge::const_raw_range const &_range,
	sge::optional_extension const &_extension
)
{
	if(_extension && extensions_.find(*_extension) == extensions_.end())
		return sge::audio::file_ptr();

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
		fcppt::make_unique_ptr<stream_type>(
			reinterpret_cast<boost::iostreams::array_source::char_type const *>(
				_range.begin()),
			reinterpret_cast<boost::iostreams::array_source::char_type const *>(
				_range.end())));

	try
	{
		return
			// Can't use make_shared here because of the unique_ptr
			sge::audio::file_ptr(
				new file(
					fcppt::move(
						raw_stream),
					sge::audio::optional_path()));
	}
	catch (audio::unsupported_format const &)
	{
		return sge::audio::file_ptr();
	}
}

sge::audio::loader_capabilities_field const
sge::vorbis::loader::capabilities() const
{
	return audio::loader_capabilities_field::null();
}

sge::extension_set const
sge::vorbis::loader::extensions() const
{
	return extensions_;
}
