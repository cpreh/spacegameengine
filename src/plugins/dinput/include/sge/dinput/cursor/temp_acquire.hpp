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


#ifndef SGE_DINPUT_CURSOR_TEMP_ACQUIRE_HPP_INCLUDED
#define SGE_DINPUT_CURSOR_TEMP_ACQUIRE_HPP_INCLUDED

#include <awl/backends/windows/event/type.hpp>
#include <sge/dinput/cursor/temp_acquire_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace dinput
{
namespace cursor
{

class temp_acquire
{
	FCPPT_NONCOPYABLE(
		temp_acquire
	);
public:
	temp_acquire(
		bool was_acquired,
		awl::backends::windows::event::type
	);

	~temp_acquire();

	bool
	needs_acquire(
		awl::backends::windows::event::type
	) const;
private:
	bool const was_acquired_;

	awl::backends::windows::event::type const event_type_;
};

}
}
}

#endif
