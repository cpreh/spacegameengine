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


#ifndef SGE_SRC_SYSTEMS_MODULES_INPUT_OBJECT_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_INPUT_OBJECT_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/system_unique_ptr.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/object_unique_ptr.hpp>
#include <sge/input/focus/object_fwd.hpp>
#include <sge/input/focus/object_unique_ptr.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/device_unique_ptr.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/input/mouse/device_unique_ptr.hpp>
#include <sge/input/plugin/collection_fwd.hpp>
#include <sge/src/systems/modules/input/cursor_modifier_fwd.hpp>
#include <sge/src/systems/modules/input/object_fwd.hpp>
#include <sge/src/systems/modules/window/object_fwd.hpp>
#include <sge/src/systems/modules/window/system_fwd.hpp>
#include <sge/systems/detail/input_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace systems
{
namespace modules
{
namespace input
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		fcppt::log::context &,
		fcppt::log::object &,
		sge::input::plugin::collection const &,
		sge::systems::detail::input const &,
		sge::systems::modules::window::system const &,
		sge::systems::modules::window::object const &
	);

	~object();

	sge::input::system &
	system() const;

	sge::input::processor &
	processor() const;

	sge::input::focus::object &
	focus_collector() const;

	sge::input::cursor::object &
	cursor_demuxer() const;

	sge::input::keyboard::device &
	keyboard_collector() const;

	sge::input::mouse::device &
	mouse_collector() const;
private:
	sge::input::system_unique_ptr const input_system_;

	sge::input::processor_unique_ptr const input_processor_;

	typedef
	fcppt::optional::object<
		sge::input::focus::object_unique_ptr
	>
	optional_focus_unique_ptr;

	optional_focus_unique_ptr const focus_collector_;

	typedef
	fcppt::optional::object<
		sge::input::cursor::object_unique_ptr
	>
	optional_cursor_unique_ptr;

	optional_cursor_unique_ptr const cursor_demuxer_;

	typedef
	fcppt::optional::object<
		sge::input::keyboard::device_unique_ptr
	>
	optional_keyboard_unique_ptr;

	optional_keyboard_unique_ptr const keyboard_collector_;

	typedef
	fcppt::optional::object<
		sge::input::mouse::device_unique_ptr
	>
	optional_mouse_unique_ptr;

	optional_mouse_unique_ptr const mouse_collector_;

	typedef
	fcppt::unique_ptr<
		sge::systems::modules::input::cursor_modifier
	>
	cursor_modifier_unique_ptr;

	typedef
	fcppt::optional::object<
		cursor_modifier_unique_ptr
	>
	optional_cursor_modifier_unique_ptr;

	optional_cursor_modifier_unique_ptr const cursor_modifier_;
};

}
}
}
}

#endif
