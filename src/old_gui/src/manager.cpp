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


#include "../../input/key_type.hpp"
#include "../../texture/handler.hpp"
#include "../manager.hpp"
#include <boost/bind.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>

sge::gui::manager::manager(const renderer_ptr rend, const input_system_ptr input_sys, font& gui_font, const image_loader_ptr il, const std::string& graphics_path)
: mod_tracker(input_sys),
  graphics_path(graphics_path),
  sprite_sys(rend, image_loader_handler(graphics_path,il)),
  input_sys(input_sys),
  gui_font(gui_font),
  il(il),
  cur(*this,point(0.5f,0.5f),dim(0.025f,0.025f)),
  mouse_scale(0.01f,0.01f), 
  _root(*this),
  _focus(&_root),
  _last_focus(_focus),
  _hover(0),
  _pressed(0),
  _last_clicked(0),
  double_click_time(200)
{
	input_sys->register_callback(boost::bind(&manager::key_callback, this, _1));
	input_sys->register_repeat_callback(boost::bind(&manager::repeat_callback, this, _1));
}

void sge::gui::manager::key_callback(const key_pair& input)
{
	const unit cursor_speed = 1;

	const key_type& key = input.first;
	const key_code code = key.code;

	const bool val = input.second != 0 ? true : false;

	switch(code) {
	case KC_MOUSEX:
		move_mouse(input.second * cursor_speed,0);
		break;
	case KC_MOUSEY:
		move_mouse(0,input.second * cursor_speed);
		break;
	case KC_MOUSEL:
		cur.pressed(val);
	default:
		if(is_mouse_key(code))
		{
			const mouse_button_event e(cur.pos(),code,mod_tracker.state(),val,key.char_code);
			if(val)
			{
				_root.mouse_down(e);
				_root.mouse_press(e);
			}
			else
			{
				_root.mouse_up(e);
				pressed(0);
			}
		}
		else if(is_keyboard_key(code))
		{
			const keyboard_button_event e(code,mod_tracker.state(),val,key.char_code);
			if(val)
			{
				focus()->key_down(e);
				focus()->key_press(e);
			}
			else
				focus()->key_up(e);
		}

		_last_focus = focus();
	}
}

void sge::gui::manager::repeat_callback(const key_type& key)
{
	if(is_mouse_key(key.code))
		_root.mouse_press(mouse_button_event(cur.pos(),key.code,mod_tracker.state(),true,key.char_code));
	else if(focus() && is_keyboard_key(key.code))
		focus()->key_press(keyboard_button_event(key.code,mod_tracker.state(),true,key.char_code));
}

void sge::gui::manager::process()
{
	sprite_sys.set_parameters();
	_root.draw(draw_event(point(0,0)));
	cur.draw();
}

void sge::gui::manager::transform(const math::space_matrix& m)
{
//	gui_font.transform(m);
	sprite_sys.transform(m);
}

void sge::gui::manager::projection(const math::space_matrix& m)
{
//	gui_font.projection(m);
	sprite_sys.projection(m);
}

void sge::gui::manager::internal_transformation(const math::space_matrix& m)
{
//	gui_font.transform(m);
	sprite_sys.transform(m);
}

void sge::gui::manager::set_matrices()
{
}

void sge::gui::manager::move_mouse(const unit x, const unit y)
{
	cur.move(x,y);
	const mouse_move_event e(cur.pos(),mod_tracker.state());
	_root.mouse_move(e);
	_root.glob_mouse_move(e);
}

void sge::gui::manager::focus(element* const e)
{
	_focus = e;
}

sge::gui::element* sge::gui::manager::focus() const
{
	return _focus;
}

sge::gui::element* sge::gui::manager::hover() const
{
	return _hover;
}

sge::gui::element* sge::gui::manager::pressed() const
{
	return _pressed;
}

sge::gui::point sge::gui::manager::cursor_pos() const
{
	return cur.pos();
}

sge::font& sge::gui::manager::get_font() const
{
	return gui_font;
}

sge::sprite_system& sge::gui::manager::get_sprite_system()
{
	return sprite_sys;
}

sge::gui::element* sge::gui::manager::root()
{
	return &_root;
}

sge::gui::element* sge::gui::manager::last_clicked() const
{
	return _last_clicked;
}

void sge::gui::manager::hover(element* const e)
{
	_hover = e;
}

void sge::gui::manager::pressed(element* const e)
{
	_pressed = e;
}

void sge::gui::manager::last_clicked(element* const e)
{
	_last_clicked = e;
}

sge::gui::manager::root_elem::root_elem(manager& m)
 : element(m,0)
{}

bool sge::gui::manager::root_elem::intersects(point) const
{
	return true;
}

sge::gui::point sge::gui::manager::root_elem::relative_pos() const
{
	return point(0,0);
}
