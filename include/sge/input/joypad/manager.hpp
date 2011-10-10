/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_INPUT_JOYPAD_MANAGER_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_MANAGER_HPP_INCLUDED

#include <sge/input/joypad/absolute_axis_event_fwd.hpp>
#include <sge/input/joypad/button_event_fwd.hpp>
#include <sge/input/joypad/device_ptr.hpp>
#include <sge/input/joypad/discover_callback.hpp>
#include <sge/input/joypad/discover_event_fwd.hpp>
#include <sge/input/joypad/relative_axis_event_fwd.hpp>
#include <sge/input/joypad/remove_callback.hpp>
#include <sge/input/joypad/remove_event_fwd.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/input/symbol.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace input
{
namespace joypad
{

class manager
{
	FCPPT_NONCOPYABLE(
		manager
	);
public:
	typedef fcppt::function::object<
		void (
			joypad::device_ptr,
			joypad::absolute_axis_event const &
		)
	> absolute_axis_callback;

	typedef fcppt::function::object<
		void (
			joypad::device_ptr,
			joypad::button_event const &
		)
	> button_callback;

	typedef fcppt::function::object<
		void (
			joypad::device_ptr,
			joypad::relative_axis_event const &
		)
	> relative_axis_callback;

	SGE_INPUT_SYMBOL
	manager(
		input::processor &,
		input::joypad::discover_callback const &,
		input::joypad::remove_callback const &,
		absolute_axis_callback const &,
		button_callback const &,
		relative_axis_callback const &
	);

	SGE_INPUT_SYMBOL
	~manager();
private:
	void
	discover(
		input::joypad::discover_event const &
	);

	void
	remove(
		input::joypad::remove_event const &
	);

	typedef boost::ptr_map<
		joypad::device_ptr,
		fcppt::signal::connection_manager
	> joypad_map;

	joypad_map devices_;

	input::joypad::discover_callback const discover_callback_;

	input::joypad::remove_callback const remove_callback_;

	absolute_axis_callback const absolute_axis_callback_;

	button_callback const button_callback_;

	relative_axis_callback const relative_axis_callback_;

	fcppt::signal::connection_manager const connections_;
};

}
}
}

#endif
