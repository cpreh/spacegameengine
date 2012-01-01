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


#include <sge/image/capabilities_field.hpp>
#include <sge/image2d/file_fwd.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/image2d/multi_system.hpp>
#include <sge/image2d/multi_system_parameters_fwd.hpp>
#include <sge/image2d/plugin.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/src/media/muxer_impl.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/filesystem/path.hpp>


sge::image2d::multi_system::multi_system(
	image2d::multi_system_parameters const &_params
)
:
	sge::image2d::system(),
	muxer_(
		_params
	)
{
}

sge::image2d::multi_system::~multi_system()
{
}

sge::image2d::file_ptr const
sge::image2d::multi_system::load(
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

sge::image2d::file_ptr const
sge::image2d::multi_system::load_raw(
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

sge::image2d::file_ptr const
sge::image2d::multi_system::create(
	image2d::view::const_object const &_object,
	sge::media::optional_extension const &_extension
)
{
	return
		muxer_.mux_extension(
			_extension
		).create(
			_object,
			_extension
		);
}

void
sge::image2d::multi_system::save(
	image2d::file const &_file,
	fcppt::filesystem::path const &_path
)
{
	return
		muxer_.mux_path(
			_path
		).save(
			_file,
			_path
		);
}

sge::image::capabilities_field const
sge::image2d::multi_system::capabilities() const
{
	return muxer_.capabilities();
}

sge::media::extension_set const
sge::image2d::multi_system::extensions() const
{
	return muxer_.extensions();
}
