/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_X11INPUT_PROCESSOR_HPP_INCLUDED
#define SGE_X11INPUT_PROCESSOR_HPP_INCLUDED

#include "device_fwd.hpp"
#include "keyboard_ptr.hpp"
#include "mouse_ptr.hpp"
#include <sge/input/processor.hpp>
#include <sge/window/instance_ptr.hpp>
#include <awl/backends/x11/event_fwd.hpp>
#include <awl/backends/x11/event_processor_ptr.hpp>
#include <awl/backends/x11/window_instance_ptr.hpp>
#include <awl/backends/x11/signal/connection_manager.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <vector>

namespace sge
{
namespace x11input
{

class processor
:
	public sge::input::processor
{
	FCPPT_NONCOPYABLE(
		processor
	)
public:
	explicit processor(
		sge::window::instance_ptr
	);

	~processor();
private:
	fcppt::signal::auto_connection
	keyboard_discover_callback(
		input::keyboard::discover_callback const &
	);

	fcppt::signal::auto_connection
	keyboard_remove_callback(
		input::keyboard::remove_callback const &
	);

	input::keyboard::device_vector const
	keyboards() const;

	fcppt::signal::auto_connection
	mouse_discover_callback(
		input::mouse::discover_callback const &
	);

	fcppt::signal::auto_connection
	mouse_remove_callback(
		input::mouse::remove_callback const &
	);

	input::mouse::device_vector const
	mice() const;

	window::instance_ptr const
	window() const;

	void
	on_acquire(
		awl::backends::x11::event const &
	);

	void
	on_release(
		awl::backends::x11::event const &
	);

	sge::window::instance_ptr const window_;

	awl::backends::x11::window_instance_ptr const x11_window_;

	awl::backends::x11::event_processor_ptr const event_processor_;

	bool acquired_;

	typedef std::vector<
		x11input::keyboard_ptr
	> keyboard_vector;

	typedef std::vector<
		x11input::mouse_ptr
	> mouse_vector;

	awl::backends::x11::signal::connection_manager const connections_;

	keyboard_vector keyboards_;

	mouse_vector mice_;
};

}
}

#endif

