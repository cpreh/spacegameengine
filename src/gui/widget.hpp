/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_GUI_WIDGET_HPP_INCLUDED
#define SGE_GUI_WIDGET_HPP_INCLUDED

#include <list>
#include <string>

#include <boost/optional.hpp>

#include "events.hpp"
#include "../iconv.hpp"

namespace sge {
namespace gui {

class manager;

class widget {
protected:
	widget *parent_;
	const std::string name_;
	typedef std::list<widget*> child_widget_list;
	child_widget_list children;
	point position_;
	dim2 size_;
	virtual void reparent(widget *);
	virtual void focus(widget*);
	virtual void blur(widget*);
public:
	typedef boost::optional<widget*> event_return_type;

	widget(widget *parent_ = 0, std::string name_ = "");
	virtual ~widget();

	virtual bool show(bool display);
	inline bool show() { return show(true ); }
	inline bool hide() { return show(false); }

	virtual void focus();
	virtual void blur();

	virtual void move(point newpos);
	inline point position() const { return position_; }
	point global_position() const;
	virtual void resize(dim2 newsize);
	inline dim2 size() const { return size_; }

	inline void parent(widget *p) { reparent(p); parent_ = p; }
	inline widget *parent() const { return parent_; }
	virtual manager *top_level_widget() const;
	inline const std::string &name() { return name_; }

protected:
	struct {
		unsigned changed : 1;
		unsigned shown   : 1;
	} flags;

	bool update();
	void change();

// events
public:
	// mouse events
	virtual event_return_type on_mouse_over    (const events::mouse_event &);
	virtual event_return_type on_mouse_out     (const events::mouse_event &);
	virtual event_return_type on_mouse_move    (const events::mouse_event &);
	virtual event_return_type on_mouse_click   (const events::mouse_event &);
	virtual event_return_type on_mouse_dblclick(const events::mouse_event &);
	virtual event_return_type on_mouse_down    (const events::mouse_event &);
	virtual event_return_type on_mouse_up      (const events::mouse_event &);
	virtual event_return_type on_mouse_wheel   (const events::mouse_wheel_event &);

	// keyboard events
	virtual event_return_type on_key_down (const events::keyboard_event &);
	virtual event_return_type on_key_up   (const events::keyboard_event &);
	virtual event_return_type on_key_press(const events::keyboard_event &);

	// drag&drop events
	//virtual event_return_type on_drag_over(const events::drag_drop_event &);
	//virtual event_return_type on_drag_out (const events::drag_drop_event &);
	//virtual event_return_type on_drag_drop(const events::drag_drop_event &);

protected:
	// focus events
	virtual void on_focus(const events::focus_event &);
	virtual void on_blur (const events::focus_event &);

	// child events
	virtual void on_child_add   (const events::child_event &);
	virtual void on_child_remove(const events::child_event &);
	virtual void on_child_show  (const events::child_event &);
	virtual void on_child_hide  (const events::child_event &);
	virtual void on_child_change(const events::child_event &);
	virtual void on_child_geom  (const events::child_event &);

	// parent events
	virtual void on_parent_destroy(const events::parent_event &);

	// paint events
	virtual bool on_update();
	virtual void on_paint (const events::paint_event &);
};

}
}

#endif // SGE_GUI_WIDGET_HPP_INCLUDED
