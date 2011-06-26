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


#include "../loader.hpp"
#include "../enable.hpp"
#include "../file.hpp"
#include "../file_ptr.hpp"
#include "../supported_extensions.hpp"
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/optional_impl.hpp>

sge::devil::loader::loader()
{
	devil::enable(
		IL_FILE_OVERWRITE
	);
}

sge::devil::loader::~loader()
{
}

sge::image2d::file_ptr const
sge::devil::loader::load(
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
sge::devil::loader::load_raw(
	sge::const_raw_range const &_range,
	sge::optional_extension const &_extension
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
sge::devil::loader::create(
	image2d::view::const_object const &_src
)
{
	return
		fcppt::make_shared_ptr<
			devil::file
		>(
			fcppt::cref(
				_src
			)
		);
}

sge::image::capabilities_field const
sge::devil::loader::capabilities() const
{
	return image::capabilities_field::null();
}

sge::extension_set const
sge::devil::loader::extensions() const
{
	return devil::supported_extensions();
}
