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


#ifndef SGE_SRC_SYSTEMS_MODULES_INPUT_OBJECT_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_INPUT_OBJECT_HPP_INCLUDED

#include <sge/plugin/manager_fwd.hpp>
#include <sge/input/plugin_ptr.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/processor_ptr.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/system_ptr.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/cursor/object_scoped_ptr.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/input/keyboard/device_scoped_ptr.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/input/mouse/device_scoped_ptr.hpp>
#include <sge/src/systems/plugin_cache_fwd.hpp>
#include <sge/src/systems/modules/input/cursor_modifier_fwd.hpp>
#include <sge/src/systems/modules/input/object_fwd.hpp>
#include <sge/src/systems/modules/window/object_fwd.hpp>
#include <sge/systems/input_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


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
		sge::systems::plugin_cache &,
		sge::plugin::manager &,
		sge::systems::input const &,
		sge::systems::modules::window::object const &
	);

	~object();

	sge::input::system &
	system() const;

	sge::input::processor &
	processor() const;

	sge::input::cursor::object &
	cursor_demuxer() const;

	sge::input::keyboard::device &
	keyboard_collector() const;

	sge::input::mouse::device &
	mouse_collector() const;
private:
	sge::input::plugin_ptr const input_plugin_;

	sge::input::system_ptr const input_system_;

	sge::input::processor_ptr const input_processor_;

	sge::input::cursor::object_scoped_ptr const cursor_demuxer_;

	sge::input::keyboard::device_scoped_ptr const keyboard_collector_;

	sge::input::mouse::device_scoped_ptr const mouse_collector_;

	typedef fcppt::scoped_ptr<
		sge::systems::modules::input::cursor_modifier
	> cursor_modifier_ptr;

	cursor_modifier_ptr const cursor_modifier_;
};

}
}
}
}

#endif
