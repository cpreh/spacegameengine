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

#include <sge/input/cursor/button_signal.hpp>
#include <sge/input/cursor/move_signal.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/scroll_signal.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/object_decl.hpp>


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

	explicit
	data(
		awl::backends::wayland::window::object const &
	);

	~data();

	awl::backends::wayland::window::object const &window_;

	sge::input::cursor::optional_position position_;

	sge::input::cursor::button_signal button_signal_;

	sge::input::cursor::move_signal move_signal_;

	sge::input::cursor::scroll_signal scroll_signal_;
};

}
}
}

#endif
