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


#include <sge/audio/file_ptr.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/loader_capabilities_field.hpp>
#include <sge/audio/loader_plugin.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/audio/multi_loader_parameters_fwd.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/src/media/muxer_impl.hpp>
#include <fcppt/filesystem/path.hpp>


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

sge::audio::file_ptr const
sge::audio::multi_loader::load(
	fcppt::filesystem::path const &_path
)
{
	return
		muxer_.mux_path(
			_path
		).load(
			_path
		);
}

sge::audio::file_ptr const
sge::audio::multi_loader::load_raw(
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	return
		muxer_.mux_extension(
			_extension
		).load_raw(
			_range,
			_extension
		);
}

sge::audio::loader_capabilities_field const
sge::audio::multi_loader::capabilities() const
{
	return muxer_.capabilities();
}

sge::media::extension_set const
sge::audio::multi_loader::extensions() const
{
	return muxer_.extensions();
}

sge::audio::multi_loader::~multi_loader()
{
}
