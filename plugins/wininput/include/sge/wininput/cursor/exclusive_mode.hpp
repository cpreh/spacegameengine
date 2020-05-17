//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WININPUT_CURSOR_EXCLUSIVE_MODE_HPP_INCLUDED
#define SGE_WININPUT_CURSOR_EXCLUSIVE_MODE_HPP_INCLUDED

#include <sge/window/object_ref.hpp>
#include <sge/wininput/cursor/exclusive_mode_fwd.hpp>
#include <awl/backends/windows/message_type.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>
#include <awl/backends/windows/window/event/generic_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace wininput
{
namespace cursor
{

class exclusive_mode
{
	FCPPT_NONCOPYABLE(
		exclusive_mode
	);
public:
	exclusive_mode(
		sge::window::object_ref,
		awl::backends::windows::window::object &
	);

	~exclusive_mode();
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
	on_temp_unacquire(
		awl::backends::windows::message_type
	);

	void
	on_temp_acquire(
		awl::backends::windows::message_type
	);

	typedef
	fcppt::optional::object<
		awl::backends::windows::message_type
	>
	optional_event_type;

	optional_event_type grab_event_;

	awl::backends::windows::window::object &window_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}
}

#endif
