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


#include <sge/audio/file.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/multi_loader_parameters_fwd.hpp>
#include <sge/audio/optional_file_unique_ptr.hpp>
#include <sge/audio/loader_plugin/traits.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/src/media/muxer_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <functional>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


sge::audio::multi_loader::multi_loader(
	sge::audio::multi_loader_parameters const &_param
)
:
	muxer_(
		_param
	)
{
}

sge::audio::optional_file_unique_ptr
sge::audio::multi_loader::load(
	boost::filesystem::path const &_path
)
{
	return
		muxer_.mux_path(
			_path,
			std::bind(
				&sge::audio::loader::load,
				std::placeholders::_1,
				_path
			)
		);
}

sge::audio::optional_file_unique_ptr
sge::audio::multi_loader::load_raw(
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	return
		muxer_.mux_extension(
			_extension,
			std::bind(
				&sge::audio::loader::load_raw,
				std::placeholders::_1,
				_range,
				_extension
			)
		);
}

sge::audio::optional_file_unique_ptr
sge::audio::multi_loader::load_stream(
	std::istream &_stream,
	sge::media::optional_extension const &_extension
)
{
	return
		muxer_.mux_extension(
			_extension,
			std::bind(
				&sge::audio::loader::load_stream,
				std::placeholders::_1,
				std::ref(
					_stream
				),
				_extension
			)
		);
}

sge::media::extension_set
sge::audio::multi_loader::extensions() const
{
	return
		muxer_.extensions();
}

sge::audio::multi_loader::~multi_loader()
{
}
