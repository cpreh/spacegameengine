//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SDLINPUT_PROCESSOR_HPP_INCLUDED
#define SGE_SDLINPUT_PROCESSOR_HPP_INCLUDED

#include <sge/input/processor.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/sdl/window/object_fwd.hpp>
#include <awl/event/base_fwd.hpp>
#include <awl/event/container.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace sdlinput
{

class processor
:
	public sge::input::processor
{
	FCPPT_NONCOPYABLE(
		processor
	);
public:
	explicit
	processor(
		sge::window::object &
	);

	~processor()
	override;
private:
	sge::window::object &
	window() const
	override;

	sge::input::cursor::container
	cursors() const
	override;

	sge::input::focus::container
	foci() const
	override;

	sge::input::joypad::container
	joypads() const
	override;

	sge::input::keyboard::container
	keyboards() const
	override;

	sge::input::mouse::container
	mice() const
	override;

	awl::event::container
	on_event(
		awl::event::base const &
	);

	sge::window::object &window_;

	awl::backends::sdl::window::object &sdl_window_;

	sge::input::cursor::shared_ptr const cursor_;

	sge::input::focus::shared_ptr const focus_;

	sge::input::keyboard::shared_ptr const keyboard_;

	sge::input::mouse::shared_ptr const mouse_;

	fcppt::signal::auto_connection const event_connection_;

};

}
}

#endif
