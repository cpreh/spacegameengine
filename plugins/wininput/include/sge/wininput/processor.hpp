//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WININPUT_PROCESSOR_HPP_INCLUDED
#define SGE_WININPUT_PROCESSOR_HPP_INCLUDED

#include <sge/input/processor.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/wininput/cursor/object_fwd.hpp>
#include <sge/wininput/focus/object_fwd.hpp>
#include <awl/backends/windows/window/event/generic_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/shared_ptr_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace wininput
{

class processor
:
	public sge::input::processor
{
	FCPPT_NONCOPYABLE(
		processor
	);
public:
	processor(
		fcppt::log::object &,
		sge::window::object &
	);

	~processor()
	override;

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
private:
	awl::event::container
	on_event(
		awl::window::event::base const &
	);

	void
	on_window_event(
		awl::backends::windows::window::event::generic const &
	);

	void
	on_focus_out();

	fcppt::log::object &log_;

	sge::window::object &window_;

	typedef
	fcppt::shared_ptr<
		sge::wininput::cursor::object
	>
	cursor_shared_ptr;
	
	cursor_shared_ptr const cursor_;

	typedef
	fcppt::shared_ptr<
		sge::wininput::focus::object
	>
	focus_shared_ptr;

	focus_shared_ptr const focus_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}

#endif
