//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <sge/wininput/cursor/define.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/window/event/generic.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::wininput::cursor::define::define(
	sge::window::object &_window
)
:
	previous_cursor_{},
	pixmap_{},
	connection_{
		_window.event_handler(
			sge::window::event_function{
				[
					this
				](
					awl::window::event::base const &_event
				){
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

sge::wininput::cursor::define::~define()
{
	fcppt::optional::maybe_void(
		previous_cursor_,
		[](
			HCURSOR const _cursor
		)
		{
			::SetCursor(
				_cursor
			);
		}
	);
}

awl::event::container
sge::wininput::cursor::define::on_event(
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
			if(
				_window_event.get().type().get()
				==
				WM_SETCURSOR
			)
				this->on_cursor();
		}
	);

	return
		awl::event::container{};
}

void
sge::wininput::cursor::define::on_cursor()
{
	HCURSOR const old(
		::SetCursor(
			pixmap_.get()
		)
	);

	if(
		!previous_cursor_.has_value()
	)
		previous_cursor_ =
			optional_hcursor(
				old
			);
}
