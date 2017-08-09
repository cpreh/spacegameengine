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


#ifndef SGE_WLINPUT_CURSOR_DATA_HPP_INCLUDED
#define SGE_WLINPUT_CURSOR_DATA_HPP_INCLUDED

#include <sge/input/cursor/optional_position.hpp>
#include <sge/wlinput/cursor/object_fwd.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <awl/event/container_reference.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace wlinput
{
namespace cursor
{

struct data
{
	FCPPT_NONCOPYABLE(
		data
	);

	data(
		sge::wlinput::cursor::object &,
		awl::backends::wayland::window::object const &,
		awl::event::container_reference
	);

	~data();

	sge::wlinput::cursor::object &cursor_;

	awl::backends::wayland::window::object const &window_;

	awl::event::container_reference const events_;

	sge::input::cursor::optional_position position_;
};

}
}
}

#endif
