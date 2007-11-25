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

#include "../inputprocessor.hpp"
#include "../../math/utility.hpp"

#include <algorithm>
#include <boost/bind.hpp>

namespace kc = sge::kc;



////////////////////////////////////////////////////////////////////////////////
// inputprocessor
//

void sge::gui::inputprocessor::init() {
	options[max_click_distance   ] =   2;
	options[double_click_duration] = 320;
	options[movement_resolution  ] =   1;
	mouse_event.global_position    = point(0, 0);
}

sge::gui::inputprocessor::inputprocessor() { init(); }
sge::gui::inputprocessor::inputprocessor(sge::input_system_ptr p) { init(); attach(p); }
sge::gui::inputprocessor::~inputprocessor() {
	detach();
	while(!ia.empty())
		detach(ia.front());
}

void sge::gui::inputprocessor::attach(sge::input_system_ptr isp) {
	detach(); // tidy up old connection
	if (!isp) return; // detach only
	is = isp;
	cc = is->register_callback(boost::bind(
		&sge::gui::inputprocessor::input_system_callback_function,
		this,
		_1
	));
	sge::window_ptr win =  isp->get_window();
	if (win) {
		clipping = rect(
			/*      x : */ 0,
			/*      y : */ 0,
			/*  width : */ win->width(),
			/* height : */ win->height()
		);

		// set cursor position first to prevent double event
		set_cursor_position(point(
			clipping.w/2,
			clipping.h/2
		));

		set_clipping(clipping);
	}
}

void sge::gui::inputprocessor::detach() {
	mouse_event.pressed =
	pending_click.button = events::mouse_event::NONE; // reset click status
	pending_click.dblclick.deactivate();

	if (cc.connected())
		cc.disconnect();
	is = sge::input_system_ptr();
}

void sge::gui::inputprocessor::attach(inputacceptor *ac) {
	ac->inputprocessor_instance = this;
	ia.push_front(ac);
}

void sge::gui::inputprocessor::detach(inputacceptor *ac) {
	inputacceptor_list::iterator it =
		std::find(ia.begin(), ia.end(), ac);
	if (it != ia.end()) {
		ia.erase(it);
		ac->inputprocessor_instance = 0;
	}
}

void sge::gui::inputprocessor::set_cursor_position(point pos) {
	point oldpos = mouse_event.global_position;
	if (oldpos != (mouse_event.global_position = pos.normalize(clipping)))
		dispatch_mouse_event(&sge::gui::inputacceptor::inject_mouse_move);
}

void sge::gui::inputprocessor::set_clipping(rect clip) {
	set_cursor_position(mouse_event.global_position.normalize(clipping = clip));
}

void sge::gui::inputprocessor::dispatch() {
	if (pending_click.dblclick.active() && pending_click.dblclick.expired())
		// we've waited so long after the first click, that the next click can't
		// trigger a double click anymore - it's time to broadcast the first click
		dispatch_click(&inputacceptor::inject_mouse_click);
}

void sge::gui::inputprocessor::input_system_callback_function(const sge::key_pair &kp) {
	const sge::key_code  key   = kp.key().code();
	const sge::key_state value = kp.value();

	if (sge::is_mouse_button(key)) {
		events::mouse_event::button btn;
		switch (key) {
			case kc::mouse_l: btn = events::mouse_event::LEFT  ; break;
			case kc::mouse_m: btn = events::mouse_event::MIDDLE; break;
			case kc::mouse_r: btn = events::mouse_event::RIGHT ; break;
			default:          btn = events::mouse_event::NONE  ; break;
		}

		if (btn != events::mouse_event::NONE) {
			events::mouse_event::button oldbutton = mouse_event.pressed;
			mouse_event.pressed = btn;
			if (value) {
				// button pressed

				if (pending_click.button == events::mouse_event::NONE)
					;
				else if (pending_click.button != btn)
					dispatch_click(&inputacceptor::inject_mouse_click);
				else if (pending_click.dblclick.active() && pending_click.dblclick.expired())
					dispatch_click(&inputacceptor::inject_mouse_click);
				// else
				//	; // we're preparing for a double click here.

				pending_click.button   = btn;
				pending_click.position = mouse_event.global_position;

				mouse_event.pressstate.insert(btn);

				dispatch_mouse_event(&inputacceptor::inject_mouse_down);

			} else {
				// button released
				mouse_event.pressstate.erase(btn);

				dispatch_mouse_event(&inputacceptor::inject_mouse_up);

				if (btn == oldbutton)
					mouse_event.pressed = events::mouse_event::NONE;

				if (btn == pending_click.button) {
					point diff = pending_click.position - mouse_event.global_position;
					if (diff.x <=  options[max_click_distance] &&
					    diff.x >= -options[max_click_distance] &&
					    diff.y <=  options[max_click_distance] &&
					    diff.y >= -options[max_click_distance]) {

						if (pending_click.dblclick.active()) {
							// yay! second hit within the clicking distance
							// and within the set amount of time -- we've
							// got a double click here!
							dispatch_click(&inputacceptor::inject_mouse_dblclick);

						} else {
							if (options[double_click_duration]) {
								// queue as waiting for a double click
								pending_click.dblclick.interval(options[double_click_duration]);
								pending_click.dblclick.activate();
								pending_click.dblclick.reset();

							} else
								// double clicking is disabled, so we can send this click instantly
								dispatch_click(&inputacceptor::inject_mouse_click);
						}

					} else // moved too far -> this is no click
					if (pending_click.dblclick.active()) // but there's still a click queued
						dispatch_click(&inputacceptor::inject_mouse_click);
				}
			}
		}

	} else if (sge::is_mouse_axis(key)) {
		point pos(0, 0);

		if (key == kc::mouse_axis_x ||
		    key == kc::mouse_axis_x_pos ||
		    key == kc::mouse_axis_x_neg) {

			// X axis
			relative_position.x += (key == kc::mouse_axis_x_neg) ? -value : value;
			if (relative_position.x >= options[movement_resolution])
				do ++pos.x;
				while ((relative_position.x -= options[movement_resolution]) >= options[movement_resolution]);
			else
			if (relative_position.x <= -options[movement_resolution])
				do --pos.x;
				while ((relative_position.x += options[movement_resolution]) <= -options[movement_resolution]);

		} else
		if (key == kc::mouse_axis_y ||
		    key == kc::mouse_axis_y_pos ||
		    key == kc::mouse_axis_y_neg) {

			// Y axis
			relative_position.y += (key == kc::mouse_axis_y_neg) ? -value : value;
			if (relative_position.y >= options[movement_resolution])
				do ++pos.y;
				while ((relative_position.y -= options[movement_resolution]) >= options[movement_resolution]);
			else
			if (relative_position.y <= -options[movement_resolution])
				do --pos.y;
				while ((relative_position.y += options[movement_resolution]) <= -options[movement_resolution]);

		} else
		if (key == kc::mouse_axis_z ||
		    key == kc::mouse_axis_z_pos ||
		    key == kc::mouse_axis_z_neg) {

			// Z axis (mouse wheel)
			if (key == kc::mouse_axis_z_neg || value == -1)
				dispatch_mouse_wheel_event(events::mouse_wheel_event::UP);
			else
				dispatch_mouse_wheel_event(events::mouse_wheel_event::DOWN);
		}

		if (pos.x || pos.y) {
			set_cursor_position(mouse_event.global_position + pos);

			if (pending_click.button != events::mouse_event::NONE) {
				point diff = pending_click.position - mouse_event.global_position;
				if (diff.x >  options[max_click_distance] ||
				    diff.x < -options[max_click_distance] ||
				    diff.y >  options[max_click_distance] ||
				    diff.y < -options[max_click_distance]) {
				    // moved outside
				    if (pending_click.dblclick.active())
						// broadcast the first click
						dispatch_click(&inputacceptor::inject_mouse_click);

					else
						// stop click logging for this click
						pending_click.button = events::mouse_event::NONE;
				}
			}
		}
	}
}

void sge::gui::inputprocessor::dispatch_click(inject_mouse_event_func f) {
	events::mouse_event me = mouse_event;
	me.global_position     = pending_click.position;
	me.pressed             = pending_click.button;
	pending_click.button   = events::mouse_event::NONE;
	pending_click.dblclick.deactivate();

	dispatch_mouse_event(f, me);
}

void sge::gui::inputprocessor::dispatch_mouse_event(inject_mouse_event_func fp) {
	dispatch_mouse_event(fp, mouse_event);
}

void sge::gui::inputprocessor::dispatch_mouse_event(inject_mouse_event_func fp, events::mouse_event &mouse_event) {
	response res = inputprocessor::response_continue;

	for (inputacceptor_list::iterator t, b=ia.begin(), e=ia.end(); (b != e) && (res == inputprocessor::response_continue); ) {
		t = b; ++b; // allow inputacceptors to detach themselves as response to events

		mouse_event.position = mouse_event.global_position - (*t)->inputprocessor_offset();
		res = ((*t)->*fp)(mouse_event);
	}
}

void sge::gui::inputprocessor::dispatch_mouse_wheel_event(events::mouse_wheel_event::direction_e dir) {
	events::mouse_wheel_event mwe;
	mwe.global_position = mouse_event.global_position;
	mwe.pressed         = mouse_event.pressed;
	mwe.pressstate      = mouse_event.pressstate;
	mwe.direction       = dir;

	response res = inputprocessor::response_continue;
	for (inputacceptor_list::iterator t, b=ia.begin(), e=ia.end(); (b != e) && (res == inputprocessor::response_continue); ) {
		t = b; ++b; // allow inputacceptors to detach themselves as response to events

		mwe.position = mwe.global_position - (*t)->inputprocessor_offset();
		res = (*t)->inject_mouse_wheel(mwe);
	}
}


////////////////////////////////////////////////////////////////////////////////
// inputacceptor
//

sge::gui::inputacceptor::inputacceptor() : inputprocessor_instance(0) {}
sge::gui::inputacceptor::inputacceptor(inputprocessor &ip) : inputprocessor_instance(0) { inputprocessor_attach(ip); }
sge::gui::inputacceptor::inputacceptor(const inputacceptor &ia) : inputprocessor_instance(0) { inputprocessor_attach(*(ia.inputprocessor_instance)); }
sge::gui::inputacceptor::~inputacceptor() { inputprocessor_detach(); }

void sge::gui::inputacceptor::inputprocessor_attach(inputprocessor &ip) { inputprocessor_detach(); ip.attach(this); }
void sge::gui::inputacceptor::inputprocessor_detach() { if (inputprocessor_instance) inputprocessor_instance->detach(this); }

sge::gui::inputprocessor::response sge::gui::inputacceptor::inject_mouse_move    (const events::mouse_event       &) { return inputprocessor::response_continue; }
sge::gui::inputprocessor::response sge::gui::inputacceptor::inject_mouse_click   (const events::mouse_event       &) { return inputprocessor::response_continue; }
sge::gui::inputprocessor::response sge::gui::inputacceptor::inject_mouse_dblclick(const events::mouse_event       &) { return inputprocessor::response_continue; }
sge::gui::inputprocessor::response sge::gui::inputacceptor::inject_mouse_down    (const events::mouse_event       &) { return inputprocessor::response_continue; }
sge::gui::inputprocessor::response sge::gui::inputacceptor::inject_mouse_up      (const events::mouse_event       &) { return inputprocessor::response_continue; }
sge::gui::inputprocessor::response sge::gui::inputacceptor::inject_mouse_wheel   (const events::mouse_wheel_event &) { return inputprocessor::response_continue; }

sge::gui::inputprocessor::response sge::gui::inputacceptor::inject_key_down      (const events::keyboard_event    &) { return inputprocessor::response_continue; }
sge::gui::inputprocessor::response sge::gui::inputacceptor::inject_key_up        (const events::keyboard_event    &) { return inputprocessor::response_continue; }
sge::gui::inputprocessor::response sge::gui::inputacceptor::inject_key_press     (const events::keyboard_event    &) { return inputprocessor::response_continue; }
