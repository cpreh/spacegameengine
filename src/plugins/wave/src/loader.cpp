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


#include <sge/audio/file_exception.hpp>
#include <sge/audio/optional_path.hpp>
#include <sge/audio/unsupported_format.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/wave/file.hpp>
#include <sge/wave/loader.hpp>
#include <sge/wave/stream_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/move.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/io/raw_container_source.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/stream.hpp>
#include <fstream>
#include <ios>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::media::extension_set const extensions_(
	fcppt::assign::make_container<
		sge::media::extension_set
	>(
		sge::media::extension(
			FCPPT_TEXT("wav")
		)
	)
);

}

sge::wave::loader::loader()
{
}

sge::wave::loader::~loader()
{
}

sge::audio::file_ptr const
sge::wave::loader::load(
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
			// Can't use make_shared here because of unique_ptr
			sge::audio::file_ptr(
				new wave::file(
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
sge::wave::loader::load_raw(
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
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
sge::wave::loader::capabilities() const
{
	return audio::loader_capabilities_field::null();
}

sge::media::extension_set const
sge::wave::loader::extensions() const
{
	return extensions_;
}
