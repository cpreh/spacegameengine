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

#include <sge/gui/widget.hpp>

#undef MOUSE_EVENT_IMPL
#define MOUSE_EVENT_IMPL(EVENT_TYPE, EVENT_INVOKE_NAME, EVENT_NAME) \
	sge::gui::widget::event_return_type sge::gui::widget::EVENT_INVOKE_NAME(const events::EVENT_TYPE &me) { \
		event_return_type retval; \
		events::EVENT_TYPE me_ = me; \
		for (child_widget_list::iterator b=sge_gui_widget_data.children.begin(), e=sge_gui_widget_data.children.end(); b != e; ++b) { \
			if (!(*b)->visible()) continue; \
			if (!me.position.within(rect(child_position(*b), (*b)->size()))) continue; \
			me_.position = me.position - child_position(*b); \
			if (retval = (*b)->EVENT_INVOKE_NAME(me_)) \
				return retval; \
		} \
		\
		return EVENT_NAME(me); \
	} \
	\
	sge::gui::widget::event_return_type sge::gui::widget::EVENT_NAME(const events::EVENT_TYPE &) { \
		return event_return_type(); \
	}

MOUSE_EVENT_IMPL(mouse_event,       invoke_mouse_click,    on_mouse_click)
MOUSE_EVENT_IMPL(mouse_event,       invoke_mouse_dblclick, on_mouse_dblclick)
MOUSE_EVENT_IMPL(mouse_event,       invoke_mouse_down,     on_mouse_down)
MOUSE_EVENT_IMPL(mouse_event,       invoke_mouse_up,       on_mouse_up)
MOUSE_EVENT_IMPL(mouse_event,       invoke_mouse_move,     on_mouse_move)
MOUSE_EVENT_IMPL(mouse_wheel_event, invoke_mouse_wheel,    on_mouse_wheel)

sge::gui::widget::event_return_type sge::gui::widget::on_mouse_over (const events::mouse_event &) { return event_return_type(); }
sge::gui::widget::event_return_type sge::gui::widget::on_mouse_out  (const events::mouse_event &) { return event_return_type(); }

sge::gui::widget::event_return_type sge::gui::widget::on_key_down (const events::keyboard_event &) { return event_return_type(); }
sge::gui::widget::event_return_type sge::gui::widget::on_key_up   (const events::keyboard_event &) { return event_return_type(); }
sge::gui::widget::event_return_type sge::gui::widget::on_key_press(const events::keyboard_event &) { return event_return_type(); }

void sge::gui::widget::on_focus(const events::focus_event &) {
	// this seems to be extremely stupid, anyhow, focussing a widget will give it
	// a lot of additional events, some even outside of its boundary or worse:
	// inside of its boundary but hitting another z-index.
	// to not force ANY widget to check for focus injected events, we install this
	// auto blur as a safety belt - the other option would've been to make focus()
	// virtual with NOOP as the default operation, forcing everyone who wants his
	// widget focussed to overwrite that function with the actual focus(this).
	// this would be even worse in terms of user friendlyness while not covering
	// cases of 3rd person(/widget) induced calls of focus(other_widget)
	blur();
}
void sge::gui::widget::on_blur (const events::focus_event &) {}

//bool sge::gui::widget::on_drag_over(const events::drag_drop_event &) { return false; }
//bool sge::gui::widget::on_drag_out (const events::drag_drop_event &) { return false; }
//bool sge::gui::widget::on_drag_drop(const events::drag_drop_event &) { return false; }

void sge::gui::widget::on_child_add   (const events::child_event &ce) { sge_gui_widget_data.children.push_back(ce.child); if (visible() && ce.child->visible()) change(); }
void sge::gui::widget::on_child_remove(const events::child_event &ce) { sge_gui_widget_data.children.remove   (ce.child); if (visible() && ce.child->visible()) change(); }
void sge::gui::widget::on_child_show  (const events::child_event &ce) { if (visible() && ce.child->visible()) change(); }
void sge::gui::widget::on_child_hide  (const events::child_event &ce) { if (visible() && ce.child->visible()) change(); }
void sge::gui::widget::on_child_change(const events::child_event &ce) { if (visible() && ce.child->visible()) change(); }
void sge::gui::widget::on_child_geom  (const events::child_event &ce) { if (visible() && ce.child->visible()) change(); }

void sge::gui::widget::on_parent_destroy    (const events::parent_event &) { reparent(0); }
void sge::gui::widget::on_parent_skin_change(const events::skin_event &se) {
	if (skin()) return;
	for (child_widget_list::iterator b=sge_gui_widget_data.children.begin(), e=sge_gui_widget_data.children.end(); b != e; ++b)
		(*b)->on_parent_skin_change(se);
}

void sge::gui::widget::on_update() {}
void sge::gui::widget::on_paint(const events::paint_event &pe) {
	paint_children(pe);
}
