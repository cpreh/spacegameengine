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


#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vf/dynamic/locked_part.hpp>


sge::renderer::vf::dynamic::locked_part::locked_part(
	sge::renderer::raw_pointer const _data,
	sge::renderer::lock_segment const &_segment,
	sge::renderer::lock_flags::method const _lock_flags
)
:
	data_(
		_data
	),
	segment_(
		_segment
	),
	lock_flags_(
		_lock_flags
	)
{
}

sge::renderer::raw_pointer
sge::renderer::vf::dynamic::locked_part::data() const
{
	return
		data_;
}

sge::renderer::vertex::first
sge::renderer::vf::dynamic::locked_part::pos() const
{
	return
		sge::renderer::vertex::first{
			segment_.pos().x()
		};
}

sge::renderer::vertex::count
sge::renderer::vf::dynamic::locked_part::count() const
{
	return
		sge::renderer::vertex::count{
			segment_.size().w()
		};
}

sge::renderer::lock_flags::method
sge::renderer::vf::dynamic::locked_part::lock_flags() const
{
	return
		lock_flags_;
}
