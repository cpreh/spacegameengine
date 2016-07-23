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


#ifndef SGE_WININPUT_FOCUS_OBJECT_HPP_INCLUDED
#define SGE_WININPUT_FOCUS_OBJECT_HPP_INCLUDED

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
#include <sge/input/key/pressed.hpp>
#include <sge/wininput/focus/object_fwd.hpp>
#include <awl/backends/windows/window/event/object_fwd.hpp>
#include <awl/backends/windows/window/event/processor_fwd.hpp>
#include <awl/backends/windows/window/event/return_type.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection_container.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge
{
namespace wininput
{
namespace focus
{

class object
:
	public sge::input::focus::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		awl::backends::windows::window::event::processor &
	);

	~object()
	override;

	fcppt::signal::auto_connection
	char_callback(
		sge::input::focus::char_callback const &
	)
	override;

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
	in_callback(
		sge::input::focus::in_callback const &
	)
	override;

	fcppt::signal::auto_connection
	out_callback(
		sge::input::focus::out_callback const &
	)
	override;
private:
	awl::backends::windows::window::event::return_type
	on_char(
		awl::backends::windows::window::event::object const &
	);

	awl::backends::windows::window::event::return_type
	on_key(
		awl::backends::windows::window::event::object const &,
		sge::input::key::pressed
	);

	awl::backends::windows::window::event::processor &event_processor_;

	sge::input::focus::char_signal char_signal_;

	sge::input::focus::key_signal key_signal_;

	sge::input::focus::key_repeat_signal key_repeat_signal_;

	sge::input::focus::in_signal in_signal_;

	sge::input::focus::out_signal out_signal_;

	fcppt::signal::auto_connection_container const connections_;
};

}
}
}

#endif
