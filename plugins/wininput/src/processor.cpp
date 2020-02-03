//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/cursor/container.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <sge/wininput/processor.hpp>
#include <sge/wininput/cursor/object.hpp>
#include <sge/wininput/focus/object.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <awl/backends/windows/window/event/generic.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/dynamic_exn.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::wininput::processor::processor(
	fcppt::log::object &_log,
	sge::window::object &_window
)
:
	log_{
		_log
	},
	window_{
		_window
	},
	cursor_{
		fcppt::make_shared_ptr<
			sge::wininput::cursor::object
		>(
			window_,
			fcppt::cast::dynamic_exn<
				awl::backends::windows::window::object &
			>(
				_window.awl_object()
			)
		)
	},
	focus_{
		fcppt::make_shared_ptr<
			sge::wininput::focus::object
		>(
			window_
		)
	},
	event_connection_{
		_window.event_handler(
			sge::window::event_function{
				[
					this
				](
					awl::window::event::base const &_event
				)
				{
					return
						this->on_event(
							_event
						);
				}
			}
		)
	}
{
}
FCPPT_PP_POP_WARNING

sge::wininput::processor::~processor()
{
}

sge::window::object &
sge::wininput::processor::window() const
{
	return
		window_;
}

sge::input::cursor::container
sge::wininput::processor::cursors() const
{
	return
		sge::input::cursor::container{
			cursor_
		};
}

sge::input::focus::container
sge::wininput::processor::foci() const
{
	return
		sge::input::focus::container{
			focus_
		};
}

sge::input::joypad::container
sge::wininput::processor::joypads() const
{
	return
		sge::input::joypad::container{};
}

sge::input::keyboard::container
sge::wininput::processor::keyboards() const
{
	return
		sge::input::keyboard::container{};
}

sge::input::mouse::container
sge::wininput::processor::mice() const
{
	return
		sge::input::mouse::container{};
}

awl::event::container
sge::wininput::processor::on_event(
	awl::window::event::base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::cast::dynamic<
			awl::backends::windows::window::event::generic const
		>(
			_event
		),
		[
			this
		](
			fcppt::reference<
				awl::backends::windows::window::event::generic const
			> const _window_event
		)
		{
			return
				this->on_window_event(
					_window_event.get()
				);
		}
	);

	return
		awl::event::container{};
}

void
sge::wininput::processor::on_window_event(
	awl::backends::windows::window::event::generic const &_event
)
{
	if(
		_event.type().get()
		==
		WM_KILLFOCUS
	)
		this->on_focus_out();
}

void
sge::wininput::processor::on_focus_out()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("focus out")
	)

	cursor_->focus_out();
}
