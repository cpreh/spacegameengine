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


#ifndef SGE_X11INPUT_FOCUS_OBJECT_HPP_INCLUDED
#define SGE_X11INPUT_FOCUS_OBJECT_HPP_INCLUDED

#include <sge/input/focus/char_callback.hpp>
#include <sge/input/focus/char_signal.hpp>
#include <sge/input/focus/in_callback.hpp>
#include <sge/input/focus/in_signal.hpp>
#include <sge/input/focus/key_callback.hpp>
#include <sge/input/focus/key_repeat_callback.hpp>
#include <sge/input/focus/key_repeat_signal.hpp>
#include <sge/input/focus/key_signal.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/focus/out_callback.hpp>
#include <sge/input/focus/out_signal.hpp>
#include <sge/x11input/input_context_fwd.hpp>
#include <sge/x11input/device/object.hpp>
#include <sge/x11input/device/parameters_fwd.hpp>
#include <sge/x11input/device/window_event_fwd.hpp>
#include <sge/x11input/focus/object_fwd.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/bitfield/object_decl.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace x11input
{
namespace focus
{

class object
:
	public sge::input::focus::object,
	public sge::x11input::device::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::x11input::device::parameters const &,
		sge::x11input::input_context const &
	);

	~object()
	override;
private:
	fcppt::signal::auto_connection
	key_callback(
		sge::input::focus::key_callback const &
	)
	override;

	fcppt::signal::auto_connection
	key_repeat_callback(
		sge::input::focus::key_repeat_callback const &
	)
	override;

	fcppt::signal::auto_connection
	char_callback(
		sge::input::focus::char_callback const &
	)
	override;

	fcppt::signal::auto_connection
	in_callback(
		sge::input::focus::in_callback const &
	)
	override;

	fcppt::signal::auto_connection
	out_callback(
		sge::input::focus::out_callback const &
	)
	override;

	void
	on_key_press(
		sge::x11input::device::window_event const &
	);

	void
	on_key_release(
		sge::x11input::device::window_event const &
	);

	sge::input::focus::key_signal key_signal_;

	sge::input::focus::key_repeat_signal key_repeat_signal_;

	sge::input::focus::char_signal char_signal_;

	sge::input::focus::in_signal in_signal_;

	sge::input::focus::out_signal out_signal_;

	awl::backends::x11::window::object const &window_;

	sge::x11input::input_context const &input_context_;

	fcppt::signal::auto_connection_container const connections_;
};

}
}
}

#endif
