/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image2d/dim.hpp>
#include <sge/libpng/byte_vector.hpp>
#include <sge/libpng/file_rep.hpp>
#include <sge/libpng/format.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::libpng::file_rep::file_rep(
	sge::image2d::dim const _size,
	sge::libpng::format const _format,
	sge::libpng::byte_vector &&_bytes
)
:
	size_(
		_size
	),
	format_(
		_format
	),
	bytes_(
		std::move(
			_bytes
		)
	)
{
}

sge::libpng::file_rep::file_rep(
	file_rep &&
) = default;

sge::libpng::file_rep &
sge::libpng::file_rep::operator=(
	file_rep &&
) = default;

sge::libpng::file_rep::~file_rep()
{
}

sge::image2d::dim const
sge::libpng::file_rep::size() const
{
	return
		size_;
}

sge::libpng::format
sge::libpng::file_rep::format() const
{
	return
		format_;
}

sge::libpng::byte_vector const &
sge::libpng::file_rep::bytes() const
{
	return
		bytes_;
}
