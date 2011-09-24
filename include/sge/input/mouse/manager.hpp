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


#ifndef SGE_INPUT_MOUSE_MANAGER_HPP_INCLUDED
#define SGE_INPUT_MOUSE_MANAGER_HPP_INCLUDED

#include <sge/input/mouse/axis_event_fwd.hpp>
#include <sge/input/mouse/button_event_fwd.hpp>
#include <sge/input/mouse/device_ptr.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/discover_event_fwd.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/remove_event_fwd.hpp>
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
namespace mouse
{

class manager
{
	FCPPT_NONCOPYABLE(
		manager
	);
public:
	typedef fcppt::function::object<
		void (
			mouse::device_ptr,
			mouse::axis_event const &
		)
	> axis_callback;

	typedef fcppt::function::object<
		void (
			mouse::device_ptr,
			mouse::button_event const &
		)
	> button_callback;

	SGE_INPUT_SYMBOL
	manager(
		input::processor &,
		input::mouse::discover_callback const &,
		input::mouse::remove_callback const &,
		axis_callback const &,
		button_callback const &
	);

	SGE_INPUT_SYMBOL
	~manager();
private:
	void
	discover(
		input::mouse::discover_event const &
	);

	void
	remove(
		input::mouse::remove_event const &
	);

	typedef boost::ptr_map<
		mouse::device_ptr,
		fcppt::signal::connection_manager
	> mouse_map;

	mouse_map devices_;

	input::mouse::discover_callback const discover_callback_;

	input::mouse::remove_callback const remove_callback_;

	axis_callback const axis_callback_;

	button_callback const button_callback_;

	fcppt::signal::connection_manager const connections_;
};

}
}
}

#endif
