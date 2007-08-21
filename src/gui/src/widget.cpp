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

sge::gui::widget::widget(widget *parent_, std::string name_)
: parent_(parent_), name_(name_) {
	if (parent_) {
		events::child_event ce;
			ce.child = this;
		parent_->on_child_add(ce);
	}
	change();
	show();
}

sge::gui::widget::~widget() {
	if (parent_) {
		events::child_event ce;
			ce.child = this;
		parent_->on_child_remove(ce);
	}
	change();
	show();
}

void sge::gui::widget::reparent(widget *p) {
	if (parent_ == p) return;
	events::child_event ce;
		ce.child = this;
	if (parent_)
		parent_->on_child_remove(ce);
	parent_ = p;
	if (parent_) {
		parent_->on_child_add(ce);
		if (flags.changed)
			parent_->change();
	}
}

bool sge::gui::widget::show(bool display) {
	if (flags.shown != display)
		flags.changed = flags.shown = display;
	return flags.shown;
}

void sge::gui::widget::move(point newpos) {
	if (position_ == newpos) return;
	position_ = newpos;
	if (parent_) {
		events::child_event ce;
		ce.child = this;
		parent_->on_child_geom(ce);
	}
}
sge::gui::point sge::gui::widget::global_position() const {
	return parent_
		? parent_->global_position() + position_
		: point(0,0);
}
void sge::gui::widget::resize(dim2 newsize) {
	if (size_ == newsize) return;
	size_ = newsize;
	if (parent_) {
		events::child_event ce;
		ce.child = this;
		parent_->on_child_geom(ce);
	}
}

void sge::gui::widget::focus() { focus(this); }
void sge::gui::widget::focus(widget *) { if (parent_) parent_->focus(this); }

void sge::gui::widget::blur() { focus(this); }
void sge::gui::widget::blur(widget *) { if (parent_) parent_->focus(this); }

sge::gui::manager *sge::gui::widget::top_level_widget() const { return parent_ ? parent_->top_level_widget() : 0; }
void sge::gui::widget::change() {
	if (flags.changed) return;
	flags.changed = true;
	events::child_event ce;
		ce.child = this;
	if (parent_)
		parent_->on_child_change(ce);
}

bool sge::gui::widget::update() { return on_update(); }

#undef MOUSE_EVENT_IMPL
#define MOUSE_EVENT_IMPL(EVENT_TYPE, EVENT_NAME) \
	bool sge::gui::widget::EVENT_NAME(const events::EVENT_TYPE &me) { \
		events::EVENT_TYPE me_ = me; \
		for (std::list<widget*>::iterator b=children.begin(), e=children.end(); b != e; ++b) { \
			if (!(*b)->flags.shown) continue; \
			if (!me.position.within(rect((*b)->position(), (*b)->size()))) continue; \
			me_.position    = me.position    - (*b)->position_; \
			me_.oldposition = me.oldposition - (*b)->position_; \
			if ((*b)->EVENT_NAME(me_)) return true; \
		} \
		return false; \
	}
MOUSE_EVENT_IMPL(mouse_event,       on_mouse_click)
MOUSE_EVENT_IMPL(mouse_event,       on_mouse_dblclick)
MOUSE_EVENT_IMPL(mouse_event,       on_mouse_down)
MOUSE_EVENT_IMPL(mouse_event,       on_mouse_up)
MOUSE_EVENT_IMPL(mouse_wheel_event, on_mouse_wheel)

bool sge::gui::widget::on_mouse_over (const events::mouse_event &) { return false; }
bool sge::gui::widget::on_mouse_out  (const events::mouse_event &) { return false; }

bool sge::gui::widget::on_mouse_move (const events::mouse_event &me) {
	bool now=false, old=false, retval=false, now_, old_;
	events::mouse_event me_ = me;
	for (std::list<widget*>::iterator b=children.begin(), e=children.end(); b != e && !(now && old); ++b) {
		if (!(*b)->flags.shown) continue;
		rect boundary((*b)->position(), (*b)->size());
		now_ = me.position   .within(boundary);
		old_ = me.oldposition.within(boundary);
		if ((now_  && !now) || (old_ && !old)) {
			me_.position    = me.position    - (*b)->position_; \
			me_.oldposition = me.oldposition - (*b)->position_; \
			now |= now_; old |= old_;
			if ((*b)->on_mouse_move(me_) && now_) retval = true;
		}
	}
	return retval;
}

bool sge::gui::widget::on_key_down (const events::keyboard_event &) { return false; }
bool sge::gui::widget::on_key_up   (const events::keyboard_event &) { return false; }
bool sge::gui::widget::on_key_press(const events::keyboard_event &) { return false; }

void sge::gui::widget::on_focus(const events::focus_event &) {}
void sge::gui::widget::on_blur (const events::focus_event &) {}

//bool sge::gui::widget::on_drag_over(const events::drag_drop_event &) { return false; }
//bool sge::gui::widget::on_drag_out (const events::drag_drop_event &) { return false; }
//bool sge::gui::widget::on_drag_drop(const events::drag_drop_event &) { return false; }

void sge::gui::widget::on_child_add   (const events::child_event &ce) { children.push_back(ce.child); if (flags.shown && ce.child->flags.shown) change(); }
void sge::gui::widget::on_child_remove(const events::child_event &ce) { children.remove(ce.child); if (flags.shown) change(); }
void sge::gui::widget::on_child_show  (const events::child_event &) { if (flags.shown) change(); }
void sge::gui::widget::on_child_hide  (const events::child_event &) { if (flags.shown) change(); }
void sge::gui::widget::on_child_change(const events::child_event &) { if (flags.shown) change(); }
void sge::gui::widget::on_child_geom  (const events::child_event &) { if (flags.shown) change(); }

void sge::gui::widget::on_parent_destroy(const events::parent_event &) { reparent(0); }

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
	for (std::list<widget*>::iterator b=children.begin(), e=children.end(); b != e; ++b) {
		pe.position.x = pe_.position.x + (*b)->position().x;
		pe.position.y = pe_.position.y + (*b)->position().y;
		(*b)->on_paint(pe);
	}
}
