//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/sdlinput/focus/translate_text_event.hpp>
#include <sge/sdlinput/joypad/discover.hpp>
#include <sge/sdlinput/joypad/map.hpp>
#include <sge/sdlinput/joypad/remove.hpp>
#include <sge/sdlinput/joypad/translate_axis_event.hpp>
#include <sge/sdlinput/joypad/translate_ball_event.hpp>
#include <sge/sdlinput/joypad/translate_button_event.hpp>
#include <sge/sdlinput/joypad/translate_hat_event.hpp>
#include <sge/sdlinput/translate/event.hpp>
#include <sge/sdlinput/translate/keyboard_event.hpp>
#include <sge/sdlinput/translate/mouse_button_event.hpp>
#include <sge/sdlinput/translate/mouse_motion_event.hpp>
#include <sge/sdlinput/translate/mouse_wheel_event.hpp>
#include <sge/sdlinput/translate/window_event.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/sdl/system/event/object.hpp>
#include <awl/backends/sdl/window/object_fwd.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <fcppt/config/external_end.hpp>


awl::event::container
sge::sdlinput::translate::event(
	fcppt::reference<
		sge::sdlinput::joypad::map
	> const _joypads,
	sge::input::cursor::shared_ptr const &_cursor,
	sge::input::focus::shared_ptr const &_focus,
	sge::input::keyboard::shared_ptr const &_keyboard,
	sge::input::mouse::shared_ptr const &_mouse,
	sge::window::object_ref const _sge_window,
	awl::backends::sdl::window::object const &_window,
	awl::backends::sdl::system::event::object const &_event
)
{
	switch(
		_event.get().type
	)
	{
	case SDL_WINDOWEVENT:
		return
			sge::sdlinput::translate::window_event(
				_cursor,
				_focus,
				_window,
				_event.get().window
			);
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		return
			sge::sdlinput::translate::keyboard_event(
				_focus,
				_keyboard,
				_window,
				_event.get().key
			);
	case SDL_TEXTINPUT:
		return
			sge::sdlinput::focus::translate_text_event(
				_focus,
				_window,
				_event.get().text
			);
	case SDL_MOUSEMOTION:
		return
			sge::sdlinput::translate::mouse_motion_event(
				_cursor,
				_mouse,
				_window,
				_event.get().motion
			);
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		return
			sge::sdlinput::translate::mouse_button_event(
				_cursor,
				_mouse,
				_window,
				_event.get().button
			);
	case SDL_MOUSEWHEEL:
		return
			sge::sdlinput::translate::mouse_wheel_event(
				_cursor,
				_mouse,
				_window,
				_event.get().wheel
			);
	case SDL_JOYAXISMOTION:
		return
			sge::sdlinput::joypad::translate_axis_event(
				_joypads.get(),
				_event.get().jaxis
			);
	case SDL_JOYBALLMOTION:
		return
			sge::sdlinput::joypad::translate_ball_event(
				_joypads.get(),
				_event.get().jball
			);
	case SDL_JOYHATMOTION:
		return
			sge::sdlinput::joypad::translate_hat_event(
				_joypads.get(),
				_event.get().jhat
			);
	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
		return
			sge::sdlinput::joypad::translate_button_event(
				_joypads.get(),
				_event.get().jbutton
			);
	case SDL_JOYDEVICEADDED:
		return
			sge::sdlinput::joypad::discover(
				_joypads,
				_sge_window,
				_event.get().jdevice
			);
	case SDL_JOYDEVICEREMOVED:
		return
			sge::sdlinput::joypad::remove(
				_joypads,
				_event.get().jdevice
			);
	//case SDL_CONTROLLERAXISMOTION:
	//case SDL_CONTROLLERBUTTONDOWN:
	//case SDL_CONTROLLERBUTTONUP:
	//case SDL_CONTROLLERDEVICEADDED:
	//case SDL_CONTROLLERDEVICEREMOVED:
	//case SDL_CONTROLLERDEVICEREMAPPED:
	}

	return
		awl::event::container{};
}
