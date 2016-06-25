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


#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/scenic/index_buffer_range.hpp>


sge::scenic::index_buffer_range::index_buffer_range(
	sge::renderer::index::first const &_first_index,
	sge::renderer::index::count const &_index_count)
:
	first_index_(
		_first_index),
	index_count_(
		_index_count)
{
}

sge::renderer::index::first const &
sge::scenic::index_buffer_range::first_index() const
{
	return
		first_index_;
}

sge::renderer::index::count const &
sge::scenic::index_buffer_range::index_count() const
{
	return
		index_count_;
}
