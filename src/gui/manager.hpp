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


#ifndef SGE_GUI_MANAGER_HPP_INCLUDED
#define SGE_GUI_MANAGER_HPP_INCLUDED

#include <map>
#include <string>
#include <boost/noncopyable.hpp>
#include <boost/signals/trackable.hpp>
#include "./cursor.hpp"
#include "../timer.hpp"
#include "../renderer/renderer.hpp"
#include "../sprite/sprite.hpp"
#include "../sprite/system.hpp"
#include "../image/image_loader.hpp"
#include "../renderer/font.hpp"
#include "../input/input_system.hpp"
#include "./types.hpp"
#include "./element.hpp"
#include "./events.hpp"
#include "./skin.hpp"

namespace sge
{
namespace gui
{

class manager : boost::noncopyable, public boost::signals::trackable {
public:
	friend class element;

	manager(renderer_ptr rend, input_system_ptr input_sys, font& f, image_loader_ptr il, const std::string& graphics_path, const unit font_height);
	void process();
	void focus(element* const e) { _focus = e; }
	element* focus() const { return _focus; }
	element* hover() const { return _hover; }
	element* pressed() const { return _pressed; }
	point cursor_pos() const { return cur.pos(); }
	font& get_font() const { return gui_font; }
	sprite_system& get_sprite_system() { return sprite_sys; }
	void font_height(unit height);
	unit font_height() const;
private:
	void key_callback(const key_pair&);
	void on_texture_not_present(const std::string& name);
	void move_mouse(unit x, unit y);

	element* root() { return &_root; }
	element* last_clicked() const { return _last_clicked; }
	void hover(element* const e) { _hover = e; }
	void pressed(element* const e) { _pressed = e; }
	void last_clicked(element* e) { _last_clicked = e; }

	struct root_elem : public element {
		root_elem(manager& m)
			: element(m,0) {}
			bool intersects(point) const { return true; }
			point relative_pos() const { return point(); }
	};

	std::string             graphics_path;
	sprite_system           sprite_sys;
	input_system_ptr        input_sys;
	font&                   gui_font;
	image_loader_ptr        il;
	unit                    _font_height;
	cursor                  cur;
	point                   mouse_scale;
	root_elem               _root;
	element*                _focus;
	element*                _last_focus;
	element*                _hover;
	element*                _pressed;
	element*                _last_clicked;
	timer                   double_click_time;
	timer                   repeat_interval;
	timer                   repeat_time;
	key_type                last_key;
	modifier_state          key_mod;
};

}
}

#endif
