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


#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/event/object.hpp>
#include <sge/opencl/event/object_unique_ptr.hpp>
#include <sge/src/opencl/event/flatten_sequence.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/raw_vector_impl.hpp>


fcppt::container::raw_vector<cl_event> const
sge::opencl::event::flatten_sequence(
	sge::opencl::event::sequence const &_event_sequence)
{
	return
		fcppt::algorithm::map<
			fcppt::container::raw_vector<cl_event>
		>(
			_event_sequence,
			[](
				sge::opencl::event::object_unique_ptr const &_ptr
			)
			{
				return
					_ptr->handle();
			}
		);
}
