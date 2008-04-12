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


#ifndef SGE_GUI_INPUTPROCESSOR_HPP_INCLUDED
#define SGE_GUI_INPUTPROCESSOR_HPP_INCLUDED

#include <list>

#include "../../src/timer.hpp"
#include "../../src/input/input_system.hpp"

#include "events.hpp"
#include "types.hpp"

namespace sge {
namespace gui {

class inputacceptor;

class inputprocessor {
public:
	typedef long option_t;
	enum option_name {
		max_click_distance,    // max. distance between button press and release
		double_click_duration, // in msec, 0 to turn off
		movement_resolution,   // lesser value is higher mouse speed
		NUM_OPTIONS
	};
	enum response {
		response_continue,
		response_discarded,
		response_accepted
	};

	inputprocessor();
	inputprocessor(input_system_ptr);
	~inputprocessor();

	void attach(input_system_ptr);
	void detach();

	void attach(inputacceptor*);
	void detach(inputacceptor*);

	void dispatch();

	inline point get_cursor_position() const { return mouse_event.position; }
	void set_cursor_position(point);

	inline rect get_clipping() const { return clipping; }
	void set_clipping(rect);

	inline const option_t option(option_name n) const { return options[n]; }
	inline void option(option_name n, option_t v) { options[n] = v; }

protected:
	option_t options[NUM_OPTIONS];
	callback_connection cc;
	input_system_ptr is;
	typedef std::list<inputacceptor*> inputacceptor_list;
	inputacceptor_list ia;

	rect clipping;
	events::mouse_event mouse_event;
	struct {
		events::mouse_event::button button;
		timer dblclick;
		point position;
	} pending_click;
	fpoint relative_position;
	enum { status_no_click, status_pending_click, status_pending_dblclick } clickstatus;

private:
	void init();
	typedef response (inputacceptor::*inject_mouse_event_func)(const events::mouse_event &);
	void dispatch_click(inject_mouse_event_func);
	void dispatch_mouse_event(inject_mouse_event_func);
	void dispatch_mouse_event(inject_mouse_event_func, events::mouse_event &);
	void dispatch_mouse_wheel_event(events::mouse_wheel_event::direction_e);
	void input_system_callback_function(const key_pair &);
};

class inputacceptor {
	friend class inputprocessor;

public:
	inputacceptor();
	inputacceptor(inputprocessor &);
	inputacceptor(const inputacceptor &);
	virtual ~inputacceptor();

	virtual point inputprocessor_offset() const = 0;

protected:
	inputprocessor *inputprocessor_instance;

	void inputprocessor_attach(inputprocessor &);
	void inputprocessor_detach();

	virtual inputprocessor::response inject_mouse_move    (const events::mouse_event       &);
	virtual inputprocessor::response inject_mouse_click   (const events::mouse_event       &);
	virtual inputprocessor::response inject_mouse_dblclick(const events::mouse_event       &);
	virtual inputprocessor::response inject_mouse_down    (const events::mouse_event       &);
	virtual inputprocessor::response inject_mouse_up      (const events::mouse_event       &);
	virtual inputprocessor::response inject_mouse_wheel   (const events::mouse_wheel_event &);

	virtual inputprocessor::response inject_key_down      (const events::keyboard_event    &);
	virtual inputprocessor::response inject_key_up        (const events::keyboard_event    &);
	virtual inputprocessor::response inject_key_press     (const events::keyboard_event    &);
};

}
}

#endif // SGE_GUI_INPUTPROCESSOR_HPP_INCLUDED
