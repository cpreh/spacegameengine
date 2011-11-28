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


#include <sge/devil/enable.hpp>
#include <sge/devil/file.hpp>
#include <sge/devil/file_ptr.hpp>
#include <sge/devil/supported_extensions.hpp>
#include <sge/devil/system.hpp>
#include <sge/image/capabilities_field.hpp>
#include <sge/image2d/file_ptr.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/filesystem/path.hpp>


sge::devil::system::system()
{
	devil::enable(
		IL_FILE_OVERWRITE
	);
}

sge::devil::system::~system()
{
}

sge::image2d::file_ptr const
sge::devil::system::load(
	fcppt::filesystem::path const &_path
)
{
	sge::devil::file_ptr const ret(
		fcppt::make_shared_ptr<
			devil::file
		>()
	);

	return
		ret->load(
			_path
		)
		?
			sge::image2d::file_ptr()
		:
			sge::image2d::file_ptr(
				ret
			);
}

sge::image2d::file_ptr const
sge::devil::system::load_raw(
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	sge::devil::file_ptr const ret(
		fcppt::make_shared_ptr<
			devil::file
		>()
	);

	return
		ret->load(
			_range,
			_extension
		)
		?
			sge::image2d::file_ptr()
		:
			sge::image2d::file_ptr(
				ret
			);
}

sge::image2d::file_ptr const
sge::devil::system::create(
	image2d::view::const_object const &_src,
	sge::media::optional_extension const &_extension
)
{
	return
		_extension
		&&
		this->extensions().count(
			*_extension
		)
		== 0u
		?
			sge::image2d::file_ptr()
		:
			fcppt::make_shared_ptr<
				devil::file
			>(
				fcppt::cref(
					_src
				)
			)
		;
}

void
sge::devil::system::save(
	image2d::file const &_file,
	fcppt::filesystem::path const &_path
)
{
	dynamic_cast<
		devil::file const &
	>(
		_file
	).save(
		_path
	);
}

sge::image::capabilities_field const
sge::devil::system::capabilities() const
{
	return image::capabilities_field::null();
}

sge::media::extension_set const
sge::devil::system::extensions() const
{
	return devil::supported_extensions();
}
