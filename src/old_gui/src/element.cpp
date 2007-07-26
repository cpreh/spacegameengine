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


#include "../element.hpp"
#include "../manager.hpp"

namespace {
	bool sort_z_order(const sge::gui::element* const l, const sge::gui::element* const r)
	{
		return l->z() < r->z();
	}
}

sge::gui::element::element(manager& m, element* const p, const bool visible, const bool enabled)
: m(m), parent(p), visible(visible), enabled(enabled), _z(0)
{
	if(!is_root())
	{
		if(!parent)
			parent = m.root();
		if(parent==this)
			throw std::logic_error("A gui element cannot be it's own parent!");
		parent->attach_child(this);
		parent->higher_children_z();
	}
}

sge::gui::element::~element()
{
	if(parent)
	{
		parent->detach_child(this);
		parent->lower_children_z();
	}
	for(child_map::iterator it = children.begin(); it != children.end(); ++it)
		(*it)->parent = 0;
}

void sge::gui::element::attach_child(element* const e)
{
	children.insert(e);
	children_z_sorted.push_front(e);
	children_z_sorted.sort(std::ptr_fun(sort_z_order));
}

void sge::gui::element::detach_child(element* const e)
{
	children.erase(e);
	children_z_sorted.erase(std::find(children_z_sorted.begin(),children_z_sorted.end(),e));
}

void sge::gui::element::show()
{
	visible = true;
	to_front();
}

void sge::gui::element::hide()
{
	visible = false;
}

bool sge::gui::element::is_visible() const
{
	return visible;
}

void sge::gui::element::set_enable(const bool _enabled)
{
	enabled = _enabled;
}

bool sge::gui::element::get_enable() const
{
	return enabled;
}

sge::gui::element* sge::gui::element::get_parent() const
{
	return parent;
}

void sge::gui::element::set_parent(element* const e)
{
	if(parent)
		parent->detach_child(this);
	e->attach_child(this);
	parent = e;
}

void sge::gui::element::click(const mouse_button_event& event)
{
	if(!enabled || !visible)
		return;
	if(event.code() == KC_MOUSEL)
	{
		if(!m.double_click_time.update() && 
		   m.last_clicked() == this)
		{
			on_double_click(event);
			return;
		}
		m.last_clicked(this);
	}
	on_click(event);
	click_signal();
}

void sge::gui::element::mouse_move(const mouse_move_event& event)
{
	if(!enabled || !visible)
		return;

	const point loc_pos = event.pos() - relative_pos();
	const mouse_move_event e(loc_pos,event.state());

	bool processed = false;
	for(children_z_sorted_list::iterator it = children_z_sorted.begin(); it != children_z_sorted.end(); ++it)
		if((*it)->intersects(loc_pos))
		{
			(*it)->mouse_move(e);
			processed = true;
		}
	if(!processed)
		m.hover(this);
	on_mouse_move(event);
	mouse_move_signal();
}

void sge::gui::element::glob_mouse_move(const mouse_move_event& event)
{
	if(!enabled || !visible)
		return;

	const point loc_pos = event.pos() - relative_pos();
	const mouse_move_event e(loc_pos,event.state());

	for(children_z_sorted_list::iterator it = children_z_sorted.begin(); it != children_z_sorted.end(); ++it)
		if((*it)->is_visible())
			(*it)->glob_mouse_move(e);
	on_glob_mouse_move(e);
}

void sge::gui::element::draw(const draw_event& event)
{
	if(!visible)
		return;

	const draw_event e(event.pos() + relative_pos());
	on_draw(e);
	
	for(children_z_sorted_list::reverse_iterator it = children_z_sorted.rbegin(); it != children_z_sorted.rend(); ++it)
		(*it)->draw(e);	
}

void sge::gui::element::key_down(const keyboard_button_event& event)
{
	if(!enabled || !visible)
		return;

	on_key_down(event);
}

void sge::gui::element::key_up(const keyboard_button_event& event)
{
	if(!enabled || !visible)
		return;
	on_key_up(event);
}

void sge::gui::element::key_press(const keyboard_button_event& event)
{
	if(!enabled || !visible)
		return;
	on_key_press(event);
}

void sge::gui::element::mouse_down(const mouse_button_event& event)
{
	if(!enabled || !visible)
		return;

	const point loc_pos = event.pos()-relative_pos();
	const mouse_button_event e(loc_pos,event.code(),event.state(),true,event.char_code());

	for(children_z_sorted_list::iterator it = children_z_sorted.begin(); it != children_z_sorted.end(); ++it)
		if((*it)->intersects(loc_pos))
		{
			(*it)->mouse_down(e);
			return;
		}
	to_front();
	m.focus(this);
	if(event.code()==KC_MOUSEL)
		m.pressed(this);
	on_mouse_down(e);
}

void sge::gui::element::mouse_up(const mouse_button_event& event)
{
	if(!enabled || !visible)
		return;

	const point loc_pos = event.pos()-relative_pos();
	const mouse_button_event e(loc_pos,event.code(),event.state(),false,event.char_code());

	for(children_z_sorted_list::iterator it = children_z_sorted.begin(); it != children_z_sorted.end(); ++it)
		if((*it)->intersects(loc_pos))
		{
			(*it)->mouse_up(e);
			return;
		}

	if(pressed() && event.code()==KC_MOUSEL)
		click(mouse_button_event(e));
	on_mouse_up(e);
}

void sge::gui::element::mouse_press(const mouse_button_event& event)
{
	if(!enabled || !visible)
		return;

	const point loc_pos = event.pos()-relative_pos();
	const mouse_button_event e(loc_pos,event.code(), event.state(), event.value(), event.char_code());

	for(children_z_sorted_list::iterator it = children_z_sorted.begin(); it != children_z_sorted.end(); ++it)
		if((*it)->intersects(loc_pos))
		{
			(*it)->mouse_press(e);
			return;
		}

	on_mouse_press(e);
}

void sge::gui::element::higher_children_z()
{
	for(children_z_sorted_list::iterator it = children_z_sorted.begin(); it != children_z_sorted.end(); ++it)
		++(*it)->_z;
	children_z_sorted.sort(std::ptr_fun(sort_z_order));
}

void sge::gui::element::lower_children_z()
{
	for(children_z_sorted_list::iterator it = children_z_sorted.begin(); it != children_z_sorted.end(); ++it)
		--(*it)->_z;
}

void sge::gui::element::to_front()
{
	_z = 0;
	if(parent)
	{
		parent->higher_children_z();
		parent->to_front();
	}
}

bool sge::gui::element::pressed() const
{
	return m.pressed() == this;
}

bool sge::gui::element::is_root() const
{
	return this == m.root();
}

unsigned sge::gui::element::z() const
{
	return _z;
}
