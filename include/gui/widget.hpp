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


#ifndef SGE_GUI_WIDGET_HPP_INCLUDED
#define SGE_GUI_WIDGET_HPP_INCLUDED

#include <list>
#include <string>

#include <boost/optional.hpp>
#include <boost/utility.hpp>

#include "../iconv.hpp"
#include "../scoped_connection.hpp"
#include "events.hpp"

namespace sge {
namespace gui {

class manager;

class widget : public sge::scoped_connection_manager, boost::noncopyable {
	friend class manager; // needed so manager can access "foreign" event handlers

protected:
	typedef std::list<widget*> child_widget_list;
	events::child_event sge_gui_widget_child_event() const;
	struct {
		widget                *parent;
		std::string            name;
		child_widget_list      children;
		point                  position;
		dim2                   size;
		bool                   visible;
		bool                   changed;
		boost::optional<color> fgcol, bgcol;
		skin_ptr               skin;
	} sge_gui_widget_data;

private:
	inline void sge_gui_widget_data_init() {
		sge_gui_widget_data.parent  = 0;
		sge_gui_widget_data.visible = true;
		change();
	}

public:
	widget(widget * const parent_=0, const std::string &name_="");
	virtual ~widget();

	inline const std::string &name() { return sge_gui_widget_data.name; }

	void change();
	inline bool changed() const { return sge_gui_widget_data.changed; }

	void        show(bool show);
	inline void show()                { show(true); }
	inline void hide()                { show(false); }
	inline bool visible()       const { return sge_gui_widget_data.visible; }

	virtual void          reparent(widget*);
	inline       widget  *parent()                 { return sge_gui_widget_data.parent; }
	inline const widget  *parent()           const { return sge_gui_widget_data.parent; }
	virtual      manager *top_level_widget();
	inline const manager *top_level_widget() const { return const_cast<widget&>(*this).top_level_widget(); }

	inline void resize(dim2 d) { if (d != sge_gui_widget_data.size) perform_resize(d); }
	inline void resize(unit w, unit h) { resize(dim2(w, h)); }
	inline dim2 size() const { return sge_gui_widget_data.size; }

	inline  void  move(point p) { if (p != sge_gui_widget_data.position) perform_move(p); }
	inline  void  move(unit x, unit y) { move(point(x, y)); }
	inline  point position() const { return sge_gui_widget_data.position; }
	virtual point child_position(const widget *) const;
	point         global_position() const;
	inline point  relative_position() const {
		return parent()
			? parent()->child_position(this)
			: point(0,0);
	}

	void focus();
	void blur();

	inline boost::optional<color> background_color() const { return sge_gui_widget_data.bgcol; }
	inline void background_color(boost::optional<color> newcol) { if (sge_gui_widget_data.bgcol != newcol) { sge_gui_widget_data.bgcol = newcol; change(); } }
	inline boost::optional<color> foreground_color() const { return sge_gui_widget_data.fgcol; }
	inline void foreground_color(boost::optional<color> newcol) { if (sge_gui_widget_data.fgcol != newcol) { sge_gui_widget_data.fgcol = newcol; change(); } }

	inline skin_ptr skin() const { return sge_gui_widget_data.skin; }
	void skin(skin_ptr newskin);
	skin_ptr drawskin() const;

protected:
	virtual void perform_resize(dim2);
	virtual void perform_move(point);
	virtual void focus(widget*);
	virtual void blur (widget*);

// events
public:
	typedef boost::optional<widget*> event_return_type;

	// mouse events
	virtual event_return_type invoke_mouse_move    (const events::mouse_event &);
	virtual event_return_type invoke_mouse_click   (const events::mouse_event &);
	virtual event_return_type invoke_mouse_dblclick(const events::mouse_event &);
	virtual event_return_type invoke_mouse_down    (const events::mouse_event &);
	virtual event_return_type invoke_mouse_up      (const events::mouse_event &);
	virtual event_return_type invoke_mouse_wheel   (const events::mouse_wheel_event &);

	// keyboard events
	virtual event_return_type on_key_down (const events::keyboard_event &);
	virtual event_return_type on_key_up   (const events::keyboard_event &);
	virtual event_return_type on_key_press(const events::keyboard_event &);

	// drag&drop events
	//virtual event_return_type invoke_drag_over(const events::drag_drop_event &);
	//virtual event_return_type invoke_drag_out (const events::drag_drop_event &);
	//virtual event_return_type invoke_drag_drop(const events::drag_drop_event &);

protected:
	// mouse events
	virtual event_return_type on_mouse_over    (const events::mouse_event &);
	virtual event_return_type on_mouse_out     (const events::mouse_event &);
	virtual event_return_type on_mouse_move    (const events::mouse_event &);
	virtual event_return_type on_mouse_click   (const events::mouse_event &);
	virtual event_return_type on_mouse_dblclick(const events::mouse_event &);
	virtual event_return_type on_mouse_down    (const events::mouse_event &);
	virtual event_return_type on_mouse_up      (const events::mouse_event &);
	virtual event_return_type on_mouse_wheel   (const events::mouse_wheel_event &);

	// drag&drop events
	//virtual event_return_type on_drag_over(const events::drag_drop_event &);
	//virtual event_return_type on_drag_out (const events::drag_drop_event &);
	//virtual event_return_type on_drag_drop(const events::drag_drop_event &);

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
	virtual void on_parent_skin_change(const events::skin_event &);

	// paint events
	void paint(const events::paint_event &);
	void paint_children(const events::paint_event &);
	virtual void on_update();
	virtual void on_paint (const events::paint_event &);


// statics
	public:
	static const boost::optional<color> default_color;
};

}
}

#endif // SGE_GUI_WIDGET_HPP_INCLUDED
