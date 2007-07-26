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

#include <string>
#include <boost/noncopyable.hpp>
#include <boost/signals/trackable.hpp>
#include "../timer.hpp"
#include "../renderer/font.hpp"
#include "../renderer/renderer.hpp"
#include "../renderer/transformable.hpp"
#include "../sprite/sprite.hpp"
#include "../sprite/system.hpp"
#include "../image/image_loader.hpp"
#include "../input/input_system.hpp"
#include "../input/key_mod_tracker.hpp"
#include "types.hpp"
#include "cursor.hpp"
#include "element.hpp"
#include "events.hpp"

namespace sge
{
namespace gui
{

class manager : public transformable, public boost::signals::trackable, boost::noncopyable {
public:
	friend class element;

	manager(renderer_ptr rend, input_system_ptr input_sys, font& f, image_loader_ptr il, const std::string& graphics_path, const unit font_height);
	void process();
	void focus(element* e);
	element* focus() const;
	element* hover() const;
	element* pressed() const;
	point cursor_pos() const;
	font& get_font() const;
	sprite_system& get_sprite_system();
	void font_height(unit height);
	unit font_height() const;
private:
	void key_callback(const key_pair&);
	void repeat_callback(const key_type&);
	void on_texture_not_present(const std::string& name);
	void move_mouse(unit x, unit y);

	void internal_transformation(const math::space_matrix&);
	void transform(const math::space_matrix&);
	void projection(const math::space_matrix&);
	void set_matrices();

	element* root();
	element* last_clicked() const;
	void hover(element* e);
	void pressed(element* e);
	void last_clicked(element* e);

	struct root_elem : public element {
		root_elem(manager& m);
		bool intersects(point) const;
		point relative_pos() const;
	};

	key_mod_tracker         mod_tracker;
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
};

}
}

#endif
