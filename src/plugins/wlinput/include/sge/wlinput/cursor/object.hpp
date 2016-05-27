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


#ifndef SGE_WLINPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_WLINPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/input/cursor/button_callback.hpp>
#include <sge/input/cursor/mode_fwd.hpp>
#include <sge/input/cursor/move_callback.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position_fwd.hpp>
#include <sge/input/cursor/scroll_callback.hpp>
#include <sge/wlinput/cursor/data.hpp>
#include <sge/wlinput/cursor/holder.hpp>
#include <sge/wlinput/cursor/object_fwd.hpp>
#include <awl/backends/wayland/seat_fwd.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>


namespace sge
{
namespace wlinput
{
namespace cursor
{

class object
:
	public sge::input::cursor::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		awl::backends::wayland::window::object const &,
		awl::backends::wayland::seat const &
	);

	~object()
	override;

	fcppt::signal::auto_connection
	button_callback(
		sge::input::cursor::button_callback const &
	)
	override;

	fcppt::signal::auto_connection
	move_callback(
		sge::input::cursor::move_callback const &
	)
	override;

	fcppt::signal::auto_connection
	scroll_callback(
		sge::input::cursor::scroll_callback const &
	)
	override;

	sge::input::cursor::optional_position
	position() const
	override;

	void
	mode(
		sge::input::cursor::mode
	)
	override;
private:
	sge::wlinput::cursor::holder const impl_;

	sge::wlinput::cursor::data data_;
};

}
}
}

#endif
