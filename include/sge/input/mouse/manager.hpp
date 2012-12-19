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


#ifndef SGE_INPUT_MOUSE_MANAGER_HPP_INCLUDED
#define SGE_INPUT_MOUSE_MANAGER_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/input/symbol.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <sge/input/mouse/button_event_fwd.hpp>
#include <sge/input/mouse/device_fwd.hpp>
#include <sge/input/mouse/discover_callback.hpp>
#include <sge/input/mouse/discover_event_fwd.hpp>
#include <sge/input/mouse/remove_callback.hpp>
#include <sge/input/mouse/remove_event_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/connection_manager.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <unordered_map>
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
	typedef std::function<
		void (
			sge::input::mouse::device &,
			sge::input::mouse::axis_event const &
		)
	> axis_callback;

	typedef std::function<
		void (
			sge::input::mouse::device &,
			sge::input::mouse::button_event const &
		)
	> button_callback;

	SGE_INPUT_SYMBOL
	manager(
		sge::input::processor &,
		sge::input::mouse::discover_callback const &,
		sge::input::mouse::remove_callback const &,
		axis_callback const &,
		button_callback const &
	);

	SGE_INPUT_SYMBOL
	~manager();
private:
	void
	discover(
		sge::input::mouse::discover_event const &
	);

	void
	remove(
		sge::input::mouse::remove_event const &
	);

	typedef std::unordered_map<
		sge::input::mouse::device *,
		fcppt::signal::connection_manager
	> mouse_map;

	mouse_map devices_;

	sge::input::mouse::discover_callback const discover_callback_;

	sge::input::mouse::remove_callback const remove_callback_;

	axis_callback const axis_callback_;

	button_callback const button_callback_;

	fcppt::signal::connection_manager const connections_;
};

}
}
}

#endif
