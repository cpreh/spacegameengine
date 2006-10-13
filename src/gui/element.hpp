/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_GUI_ELEMENT_HPP_INCLUDED
#define SGE_GUI_ELEMENT_HPP_INCLUDED

#include <set>
#include <list>
#include <string>
#include <boost/signal.hpp>
#include <boost/utility.hpp>
#include "../types.hpp"
#include "../shared_ptr.hpp"
#include "../renderer/renderer.hpp"
#include "../input/key_type.hpp"
#include "../math/rect.hpp"
#include "./events.hpp"
#include "./types.hpp"

namespace sge
{
namespace gui
{

class manager;

class element : boost::noncopyable {
public:
	virtual ~element();
	virtual void attach_child(element* element);
	virtual void detach_child(element* element);

	void set_parent(element* element);
	element* get_parent() const;
	void show();
	void hide();
	bool is_visible() const;
	void set_enable(bool enabled);
	bool get_enable() const;
	void to_front();
	bool pressed() const;
	virtual bool intersects(point p) const = 0;
	unsigned z() const { return _z; }

	typedef boost::signal<void ()> signal_type;
	signal_type mouse_move_signal,
	            glob_mouse_move_signal,
	            mouse_down_signal,
	            mouse_up_signal,
	            mouse_press_signal,
	            click_signal,
	            key_down_signal,
	            key_up_signal,
	            key_press_signal;
protected:
	element(manager& m, element* parent, bool visible = true, bool enabled = true);
	manager& m;
private:
	virtual point relative_pos() const = 0;

	virtual void on_mouse_move(const mouse_move_event&) {}
	virtual void on_glob_mouse_move(const mouse_move_event&) {}
	virtual void on_mouse_down(const mouse_button_event&) {}
	virtual void on_mouse_up(const mouse_button_event&) {}
	virtual void on_mouse_press(const mouse_button_event&) {}
	virtual void on_click(const mouse_button_event&) {}
	virtual void on_double_click(const mouse_button_event&) {}
	virtual void on_key_down(const keyboard_button_event&) {}
	virtual void on_key_up(const keyboard_button_event&) {}
	virtual void on_key_press(const keyboard_button_event&) {}
	virtual void on_draw(const draw_event&) {}

	void mouse_move(const mouse_move_event& event);
	void glob_mouse_move(const mouse_move_event& event);
	void mouse_down(const mouse_button_event& event);
	void mouse_up(const mouse_button_event& event);
	void mouse_press(const mouse_button_event& event);
	void click(const mouse_button_event& event);
	void key_down(const keyboard_button_event& event);
	void key_up(const keyboard_button_event& event);
	void key_press(const keyboard_button_event& event);
	void draw(const draw_event& event);

	void higher_children_z();
	void lower_children_z();
	bool is_root() const;

	typedef std::set<element*> child_map;
	typedef std::list<element*> children_z_sorted_list;

	element*                parent;
	bool                    visible;
	bool                    enabled;
	unsigned                _z;
	child_map               children;
	children_z_sorted_list  children_z_sorted;

	friend class manager;
};

typedef shared_ptr<element> element_ptr;

}
}

#endif
