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

#include "../widget.hpp"

#include "../defaultskin.hpp"
#include "../manager.hpp"

sge::gui::events::child_event sge::gui::widget::sge_gui_widget_child_event() const {
	events::child_event ce;
	ce.child = const_cast<widget*>(this);
	return ce;
}

sge::gui::widget::widget() {
	sge_gui_widget_data_init();
}

sge::gui::widget::widget(widget *parent_, std::string name_) {
	sge_gui_widget_data_init();
	sge_gui_widget_data.name = name_;
	reparent(parent_);
}

sge::gui::widget::~widget() {
	reparent(0);
}

void sge::gui::widget::change() {
	if (changed()) return;
	sge_gui_widget_data.changed = true;
	if (parent())
		parent()->on_child_change(sge_gui_widget_child_event());
}

void sge::gui::widget::show(bool newvis) {
	if (visible() == newvis)
		return;

	sge_gui_widget_data.visible = newvis;
	if (parent()) {
		if (newvis)
			parent()->on_child_show(sge_gui_widget_child_event());
		else
			parent()->on_child_hide(sge_gui_widget_child_event());
	}
}

void sge::gui::widget::reparent(sge::gui::widget *newparent) {
	if (sge_gui_widget_data.parent == newparent) return;

	manager *oldmgr = top_level_widget();

	if (parent())
		sge_gui_widget_data.parent->on_child_remove(sge_gui_widget_child_event());
	sge_gui_widget_data.parent = newparent;
	if (parent()) {
		parent()->on_child_add(sge_gui_widget_child_event());
		if (changed())
			parent()->on_child_change(sge_gui_widget_child_event());
	}

	if (oldmgr && oldmgr != top_level_widget())
		oldmgr->widget_removed(this);
}

sge::gui::manager *sge::gui::widget::top_level_widget() {
	return parent()
		? parent()->top_level_widget()
		: 0;
}

void sge::gui::widget::perform_resize(sge::gui::dim2 newsize) {
	if (sge_gui_widget_data.size == newsize) return;
	sge_gui_widget_data.size = newsize;
	if (parent())
		parent()->on_child_geom(sge_gui_widget_child_event());
}

void sge::gui::widget::perform_move(sge::gui::point newpos) {
	if (sge_gui_widget_data.position == newpos) return;
	sge_gui_widget_data.position = newpos;
	if (parent())
		parent()->on_child_geom(sge_gui_widget_child_event());
}

sge::gui::point sge::gui::widget::child_position(const widget *w) const {
	return w->position();
}

sge::gui::point sge::gui::widget::global_position() const {
	return parent()
		? parent()->child_position(this) + parent()->global_position()
		: point(0,0);
}

void sge::gui::widget::focus() { focus(this); }
void sge::gui::widget::blur () { blur (this); }

void sge::gui::widget::focus(widget *w) { if (parent()) parent()->focus(w); }
void sge::gui::widget::blur (widget *w) { if (parent()) parent()->blur (w); }

void sge::gui::widget::paint(const events::paint_event &pe) {
	if (changed()) {
		sge_gui_widget_data.changed = false;
		on_update();
	}
	on_paint(pe);
}

void sge::gui::widget::skin(skin_ptr newskin) {
	if (sge_gui_widget_data.skin != newskin) {
		if ((newskin && newskin != drawskin()) ||
		    ((parent() && !newskin) && newskin != parent()->drawskin())) {
			events::skin_event se;
				se.skin = newskin;
			for (child_widget_list::iterator b=sge_gui_widget_data.children.begin(), e=sge_gui_widget_data.children.end(); b != e; ++b)
				(*b)->on_parent_skin_change(se);
			change();
		}
		sge_gui_widget_data.skin = newskin;
	}
}

sge::gui::skin_ptr sge::gui::widget::drawskin() const {
	return skin()
		? skin()
		: parent()
			? parent()->drawskin()
			: defaultskin::get();
}



////////////////////////////////////////////////////////////////////////////////
// statics

const boost::optional<sge::gui::color> sge::gui::widget::default_color;
