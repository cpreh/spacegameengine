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
#include <sge/audio/load_stream_result.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/multi_loader_parameters_fwd.hpp>
#include <sge/audio/loader_plugin/traits.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <sge/src/media/muxer_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::audio::multi_loader::multi_loader(
	sge::audio::multi_loader_parameters const &_param
)
:
	sge::audio::loader(),
	muxer_(
		_param
	)
{
}

sge::audio::load_stream_result
sge::audio::multi_loader::load_stream(
	sge::media::stream_unique_ptr &&_stream,
	sge::media::optional_extension const &_extension,
	sge::media::optional_name const &_name
)
{
	return
		muxer_.mux_stream(
			std::move(
				_stream
			),
			_extension,
			_name
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
