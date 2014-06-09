/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_INPUT_MOUSE_COLLECTOR_HPP_INCLUDED
#define SGE_INPUT_MOUSE_COLLECTOR_HPP_INCLUDED

#include <sge/input/processor_fwd.hpp>
#include <sge/input/symbol.hpp>
#include <sge/input/mouse/axis_callback.hpp>
#include <sge/input/mouse/axis_event_fwd.hpp>
#include <sge/input/mouse/axis_signal.hpp>
#include <sge/input/mouse/button_callback.hpp>
#include <sge/input/mouse/button_event_fwd.hpp>
#include <sge/input/mouse/button_signal.hpp>
#include <sge/input/mouse/collector_fwd.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/input/mouse/manager.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace input
{
namespace mouse
{

class collector
:
	public sge::input::mouse::device
{
	FCPPT_NONCOPYABLE(
		collector
	);
public:
	SGE_INPUT_SYMBOL
	explicit
	collector(
		sge::input::processor &
	);

	SGE_INPUT_SYMBOL
	~collector()
	override;

	SGE_INPUT_SYMBOL
	fcppt::signal::auto_connection
	axis_callback(
		sge::input::mouse::axis_callback const &
	)
	override;

	SGE_INPUT_SYMBOL
	fcppt::signal::auto_connection
	button_callback(
		sge::input::mouse::button_callback const &
	)
	override;

	SGE_INPUT_SYMBOL
	sge::input::mouse::info const &
	info() const
	override;
private:
	void
	axis_callback_internal(
		sge::input::mouse::device &,
		sge::input::mouse::axis_event const &
	);

	void
	button_callback_internal(
		sge::input::mouse::device &,
		sge::input::mouse::button_event const &
	);

	sge::input::mouse::manager manager_;

	sge::input::mouse::info info_;

	sge::input::mouse::axis_signal axis_signal_;

	sge::input::mouse::button_signal button_signal_;
};

}
}
}

#endif
