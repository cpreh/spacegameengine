/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

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

#include <sge/gui/manager.hpp>

#define MOUSE_EVENT_PROLOG \
	if (me.position.x >= size().w || me.position.x < 0 || \
	    me.position.y >= size().h || me.position.y < 0) \
		return inputprocessor::response_continue; // not hit


#define MOUSE_EVENT_INJECT_TO_FOCUS(FUNC) \
	if (currently_focused_widget) { \
		events::mouse_event me2 = me; \
		me2.is_focus_injection = true; \
		me2.position = me2.global_position - currently_focused_widget->global_position(); \
		currently_focused_widget->FUNC(me2); \
	}

#define MOUSE_EVENT_EPILOG \
	return evret \
		? *evret \
			? inputprocessor::response_accepted \
			: inputprocessor::response_discarded \
		: inputprocessor::response_continue;

sge::gui::point sge::gui::manager::inputprocessor_offset() const { return position(); }

sge::gui::inputprocessor::response sge::gui::manager::inject_mouse_move    (const events::mouse_event       &me) {
	MOUSE_EVENT_PROLOG;
	MOUSE_EVENT_INJECT_TO_FOCUS(on_mouse_move);

	widget::event_return_type evret = invoke_mouse_move(me);

	widget *new_hovered_widget = evret ? *evret : 0;
	if (evret)
		new_hovered_widget = *evret;

	if (new_hovered_widget != previously_hovered_widget) {
		if (previously_hovered_widget)
			previously_hovered_widget->on_mouse_out(me);
		if (new_hovered_widget)
			new_hovered_widget->on_mouse_over(me);
	}

	previously_hovered_widget = new_hovered_widget;

	MOUSE_EVENT_EPILOG;
}

sge::gui::inputprocessor::response sge::gui::manager::inject_mouse_click   (const events::mouse_event       &me) {
	MOUSE_EVENT_PROLOG;
	MOUSE_EVENT_INJECT_TO_FOCUS(on_mouse_click);
	widget::event_return_type evret = invoke_mouse_click(me);
	MOUSE_EVENT_EPILOG;
}

sge::gui::inputprocessor::response sge::gui::manager::inject_mouse_dblclick(const events::mouse_event       &me) {
	MOUSE_EVENT_PROLOG;
	MOUSE_EVENT_INJECT_TO_FOCUS(on_mouse_dblclick);
	widget::event_return_type evret = invoke_mouse_dblclick(me);
	MOUSE_EVENT_EPILOG;
}

sge::gui::inputprocessor::response sge::gui::manager::inject_mouse_down    (const events::mouse_event       &me) {
	MOUSE_EVENT_PROLOG;
	MOUSE_EVENT_INJECT_TO_FOCUS(on_mouse_down);
	widget::event_return_type evret = invoke_mouse_down(me);
	MOUSE_EVENT_EPILOG;
}

sge::gui::inputprocessor::response sge::gui::manager::inject_mouse_up      (const events::mouse_event       &me) {
	MOUSE_EVENT_PROLOG;
	MOUSE_EVENT_INJECT_TO_FOCUS(on_mouse_up);
	widget::event_return_type evret = invoke_mouse_up(me);
	MOUSE_EVENT_EPILOG;
}

sge::gui::inputprocessor::response sge::gui::manager::inject_mouse_wheel   (const events::mouse_wheel_event &me) {
	MOUSE_EVENT_PROLOG;
	widget::event_return_type evret = invoke_mouse_wheel(me);
	MOUSE_EVENT_EPILOG;
}
