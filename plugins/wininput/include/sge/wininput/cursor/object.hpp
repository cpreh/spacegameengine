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


#ifndef SGE_WININPUT_CURSOR_OBJECT_HPP_INCLUDED
#define SGE_WININPUT_CURSOR_OBJECT_HPP_INCLUDED

#include <sge/input/cursor/button_code_fwd.hpp>
#include <sge/input/cursor/button_pressed.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position_fwd.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/scroll_code_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/wininput/cursor/exclusive_mode_fwd.hpp>
#include <sge/wininput/cursor/object_fwd.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/event/generic_fwd.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace wininput
{
namespace cursor
{

class object
:
	public
		sge::input::cursor::object,
	public
		fcppt::enable_shared_from_this<
			sge::wininput::cursor::object
		>
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::window::object &,
		awl::backends::windows::window::object &
	);

	~object()
	override;

	sge::input::cursor::optional_position
	position() const
	override;

	void
	mode(
		sge::input::cursor::mode
	)
	override;

	sge::window::object &
	window() const
	override;

	void
	focus_out();
private:
	void
	focus_in();

	void
	make_grab();

	awl::event::container
	on_event(
		awl::window::event::base const &
	);

	awl::event::optional_base_unique_ptr
	on_window_event(
		awl::backends::windows::window::event::generic const &
	);

	awl::event::base_unique_ptr
	on_move_event(
		awl::backends::windows::window::event::generic const &
	);

	awl::event::base_unique_ptr
	on_button_event(
		awl::backends::windows::window::event::generic const &,
		sge::input::cursor::button_code,
		sge::input::cursor::button_pressed
	);

	awl::event::base_unique_ptr
	on_scroll_event(
		awl::backends::windows::window::event::generic const &,
		sge::input::cursor::scroll_code
	);

	sge::window::object &window_;

	awl::backends::windows::window::object &windows_window_;

	typedef
	fcppt::unique_ptr<
		sge::wininput::cursor::exclusive_mode
	>
	exclusive_mode_unique_ptr;

	typedef
	fcppt::optional::object<
		exclusive_mode_unique_ptr
	>
	optional_exclusive_mode_unique_ptr;

	sge::input::cursor::mode mode_;

	bool has_focus_;

	optional_exclusive_mode_unique_ptr exclusive_mode_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}
}

#endif
