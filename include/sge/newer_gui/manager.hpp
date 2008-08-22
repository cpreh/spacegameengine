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


#ifndef SGE_GUI_MANAGER_HPP_INCLUDED
#define SGE_GUI_MANAGER_HPP_INCLUDED

#include "canvas.hpp"
#include "inputprocessor.hpp"
#include "widget.hpp"

namespace sge {
namespace gui {

class manager : public widget, public inputacceptor {
	friend class widget;

public:
	manager();
	manager(const dim2 &);
	manager(inputprocessor &);
	manager(inputprocessor &, const point &, const dim2 &);
	manager(inputprocessor &, const rect &);
	~manager();

	manager *top_level_widget();
	void resize(dim2);

	sge::virtual_texture_ptr to_texture(sge::texture_manager &texmgr);
	void free_texture();

public:
	// inputacceptor api
	using inputacceptor::inputprocessor_attach;
	using inputacceptor::inputprocessor_detach;

	point inputprocessor_offset() const;

	inputprocessor::response inject_mouse_move    (const events::mouse_event       &);
	inputprocessor::response inject_mouse_click   (const events::mouse_event       &);
	inputprocessor::response inject_mouse_dblclick(const events::mouse_event       &);
	inputprocessor::response inject_mouse_down    (const events::mouse_event       &);
	inputprocessor::response inject_mouse_up      (const events::mouse_event       &);
	inputprocessor::response inject_mouse_wheel   (const events::mouse_wheel_event &);

//	inputprocessor::response inject_key_down      (const events::keyboard_event    &);
//	inputprocessor::response inject_key_up        (const events::keyboard_event    &);
//	inputprocessor::response inject_key_press     (const events::keyboard_event    &);

protected:
	canvas framebuffer;
	void focus(widget*);
	void blur (widget*);

private:
	sge::virtual_texture_ptr last_texture;
	void widget_removed(widget*);
	widget *previously_hovered_widget,
	       *currently_focused_widget;
	void init();
};

}
}

#endif // SGE_GUI_MANAGER_HPP_INCLUDED
