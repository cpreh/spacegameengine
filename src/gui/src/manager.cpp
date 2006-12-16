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
#include "../manager.hpp"
#include "../skin.hpp"
#include "../../sprite/handler.hpp"
#include <boost/bind.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>

sge::gui::manager::manager(const renderer_ptr rend, const input_system_ptr input_sys, font& gui_font, const image_loader_ptr il, const std::string& graphics_path, const unit _font_height)
: graphics_path(graphics_path),
  sprite_sys(rend, image_loader_handler(graphics_path,il)),
  input_sys(input_sys),
  gui_font(gui_font),
  il(il),
  _font_height(_font_height),
  cur(*this,point(0.5f,0.5f),dim(0.025f,0.025f)),
  mouse_scale(0.01f,0.01f), 
  _root(*this),
  _focus(&_root),
  _last_focus(_focus),
  _hover(0),
  _pressed(0),
  _last_clicked(0),
  double_click_time(200),
  repeat_interval(50),
  repeat_time(500),
  last_key("") 
{
	input_sys->register_callback(boost::bind(&manager::key_callback, this, _1));
}

void sge::gui::manager::key_callback(const key_pair& input)
{
	const unit cursor_speed = 1;

	const key_type& key = input.first;
	const key_code code = key.code;

	const bool val = input.second != 0 ? true : false;

	switch(code) {
	case KC_LCTRL:
	case KC_RCTRL:
		key_mod.ctrl_down = val;
		break;
	case KC_LSHIFT:
	case KC_RSHIFT:
		key_mod.shift_down = val;
		break;
	case KC_ALT:
		key_mod.alt_down = val;
		break;
	case KC_ALTGR:
		key_mod.alt_down = key_mod.ctrl_down = val;
		break;
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
			const mouse_button_event e(cur.pos(),code,key_mod,val,key.char_code);
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
			const keyboard_button_event e(code,key_mod,val,key.char_code);
			if(val)
			{
				focus()->key_down(e);
				focus()->key_press(e);
			}
			else
				focus()->key_up(e);
		}

		if(val == false)
			repeat_time.deactivate();
		else
			repeat_time.activate();
		if(key != last_key || _last_focus != focus())
			repeat_time.reset();
		
		last_key = key;
		_last_focus = focus();
	}
}

void sge::gui::manager::process()
{
	get_font().height(font_height());
	if(repeat_time.expired() && repeat_interval.update())
	{
		if(is_mouse_key(last_key.code))
			_root.mouse_press(mouse_button_event(cur.pos(),last_key.code,key_mod,true,last_key.char_code));
		else if(is_keyboard_key(last_key.code))
			focus()->key_press(keyboard_button_event(last_key.code,key_mod,true,last_key.char_code));
	}

	sprite_sys.set_parameters();
	gui_font.transform(matrix4x4<space_unit>());
	sprite_sys.get_renderer()->set_transformation(matrix4x4<space_unit>());
	_root.draw(draw_event(point(0,0)));
	cur.draw();
}

void sge::gui::manager::move_mouse(const unit x, const unit y)
{
	cur.move(x,y);
	const mouse_move_event e(cur.pos(),key_mod);
	_root.mouse_move(e);
	_root.glob_mouse_move(e);
}

void sge::gui::manager::font_height(const unit h)
{
	_font_height = h;
}

sge::gui::unit sge::gui::manager::font_height() const
{
	return _font_height;
}
