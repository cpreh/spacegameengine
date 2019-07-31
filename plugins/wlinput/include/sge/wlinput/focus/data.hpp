//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_FOCUS_DATA_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_DATA_HPP_INCLUDED

#include <sge/input/key/optional_code.hpp>
#include <sge/wlinput/xkb_context_fwd.hpp>
#include <sge/wlinput/focus/object_fwd.hpp>
#include <sge/wlinput/focus/optional_keymap.hpp>
#include <sge/wlinput/focus/optional_state.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <awl/event/container_reference.hpp>
#include <awl/system/event/processor_fwd.hpp>
#include <awl/timer/unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace wlinput
{
namespace focus
{

struct data
{
	FCPPT_NONCOPYABLE(
		data
	);

	data(
		fcppt::log::object &,
		sge::wlinput::focus::object &,
		sge::wlinput::xkb_context const &,
		awl::system::event::processor &,
		awl::backends::wayland::window::object const &,
		awl::event::container_reference
	);

	~data();

	fcppt::log::object &log_;

	sge::wlinput::focus::object &focus_;

	sge::wlinput::xkb_context const &xkb_context_;

	awl::system::event::processor &processor_;

	awl::backends::wayland::window::object const &window_;

	awl::event::container_reference const events_;

	bool entered_;

	sge::wlinput::focus::optional_keymap xkb_keymap_;

	sge::wlinput::focus::optional_state xkb_state_;

	sge::input::key::optional_code last_pressed_;

	fcppt::optional::object<
		awl::timer::unique_ptr
	>
	repeat_timer_;
};

}
}
}

#endif
