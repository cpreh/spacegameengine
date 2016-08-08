/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/audio/exception.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/load.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/optional_file_unique_ptr.hpp>
#include <sge/media/impl/load.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::audio::optional_file_unique_ptr
sge::audio::load(
	sge::audio::loader &_loader,
	boost::filesystem::path const &_path
)
{
	return
		sge::media::impl::load<
			sge::audio::file_unique_ptr,
			sge::audio::exception
		>(
			_loader,
			_path
		);
}
