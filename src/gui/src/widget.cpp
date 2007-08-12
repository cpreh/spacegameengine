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

#include "../widget.hpp"

sge::gui::widget::widget(widget *parent_, sge::string)
: parent_(parent_), name_(name_) {
	if (parent_) {
		events::child_event ce;
			ce.child = this;
		parent_->on_child_add(ce);
	}
}

sge::gui::widget::~widget() {
	if (parent_) {
		events::child_event ce;
			ce.child = this;
		parent_->on_child_remove(ce);
	}
}

void sge::gui::widget::reparent(widget *p) {
	if (parent_ == p) return;
	events::child_event ce;
		ce.child = this;
	if (parent_)
		parent_->on_child_remove(ce);
	parent_ = p;
	if (parent_)
		parent_->on_child_add(ce);
}

bool sge::gui::widget::show(bool display) {
	if (flags.shown != display)
		flags.changed = flags.shown = display;
	return flags.shown;
}

void sge::gui::widget::focus() { focus(this); }
void sge::gui::widget::focus(widget *) { if (parent_) parent_->focus(this); }

void sge::gui::widget::blur() { focus(this); }
void sge::gui::widget::blur(widget *) { if (parent_) parent_->focus(this); }

sge::gui::manager *sge::gui::widget::root() const { return parent_ ? parent_->root() : 0; }
void sge::gui::widget::change() {
	if (flags.changed) return;
	flags.changed = true;
	events::child_event ce;
		ce.child = this;
	if (parent_)
		parent_->on_child_change(ce);
}

bool sge::gui::widget::update() { return on_update(); }

bool sge::gui::widget::on_mouse_over    (const events::mouse_event &) { return false; }
bool sge::gui::widget::on_mouse_out     (const events::mouse_event &) { return false; }
bool sge::gui::widget::on_mouse_move    (const events::mouse_event &) { return false; }
bool sge::gui::widget::on_mouse_click   (const events::mouse_event &) { return false; }
bool sge::gui::widget::on_mouse_dblclick(const events::mouse_event &) { return false; }
bool sge::gui::widget::on_mouse_down    (const events::mouse_event &) { return false; }
bool sge::gui::widget::on_mouse_up      (const events::mouse_event &) { return false; }
bool sge::gui::widget::on_mouse_wheel   (const events::mouse_event &) { return false; }

bool sge::gui::widget::on_key_down (const events::keyboard_event &) { return false; }
bool sge::gui::widget::on_key_up   (const events::keyboard_event &) { return false; }
bool sge::gui::widget::on_key_press(const events::keyboard_event &) { return false; }

void sge::gui::widget::on_focus(const events::focus_event &) {}
void sge::gui::widget::on_blur (const events::focus_event &) {}

//bool sge::gui::widget::on_drag_over(const events::drag_drop_event &) { return false; }
//bool sge::gui::widget::on_drag_out (const events::drag_drop_event &) { return false; }
//bool sge::gui::widget::on_drag_drop(const events::drag_drop_event &) { return false; }

void sge::gui::widget::on_child_add   (const events::child_event &ce) { children.push_back(ce.child); }
void sge::gui::widget::on_child_remove(const events::child_event &ce) { children.remove(ce.child); }
void sge::gui::widget::on_child_show  (const events::child_event &) { if (flags.shown) change(); }
void sge::gui::widget::on_child_hide  (const events::child_event &) { if (flags.shown) change(); }
void sge::gui::widget::on_child_change(const events::child_event &) { if (flags.shown) change(); }

void sge::gui::widget::on_parent_destroy(const events::parent_event &pe) { reparent(0); }

bool sge::gui::widget::on_update() {
	if (!flags.changed) return false;
	if (!flags.shown)   return false;
	for (std::list<widget*>::iterator b=children.begin(), e=children.end(); b != e; ++b)
		(*b)->update();
	return true;
}

void sge::gui::widget::on_paint (const events::paint_event &pe_) {
	update();
	events::paint_event pe = pe_;

}
