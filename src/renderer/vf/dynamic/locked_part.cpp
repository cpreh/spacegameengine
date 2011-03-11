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


#include <sge/renderer/vf/dynamic/locked_part.hpp>

sge::renderer::vf::dynamic::locked_part::locked_part(
	renderer::raw_pointer const _data,
	renderer::size_type const _pos,
	renderer::size_type const _count,
	bool const _read,
	bool const _write
)
:
	data_(_data),
	pos_(_pos),
	count_(_count),
	read_(_read),
	write_(_write)
{
}

sge::renderer::raw_pointer
sge::renderer::vf::dynamic::locked_part::data() const
{
	return data_;
}

sge::renderer::size_type
sge::renderer::vf::dynamic::locked_part::pos() const
{
	return pos_;
}

sge::renderer::size_type
sge::renderer::vf::dynamic::locked_part::count() const
{
	return count_;
}

bool
sge::renderer::vf::dynamic::locked_part::read() const
{
	return read_;
}

bool
sge::renderer::vf::dynamic::locked_part::write() const
{
	return write_;
}
