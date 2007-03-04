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

sge::gui::manager::manager(const renderer_ptr rend, const input_system_ptr input_sys, font& gui_font, const image_loader_ptr il, const std::string& graphics_path, const unit _font_height)
: repeater(input_sys, 50, 500),
  mod_tracker(input_sys),
  graphics_path(graphics_path),
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
  double_click_time(200)
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

		if(_last_focus != focus())
			repeater.repeat_timer().reset();

		_last_focus = focus();
	}
}

void sge::gui::manager::process()
{
	get_font().height(font_height());
	const key_type key = repeater.repeated_key();
	if(key != key_repeater::no_key)
	{
		if(is_mouse_key(key.code))
			_root.mouse_press(mouse_button_event(cur.pos(),key.code,mod_tracker.state(),true,key.char_code));
		else if(is_keyboard_key(key.code))
			focus()->key_press(keyboard_button_event(key.code,mod_tracker.state(),true,key.char_code));
	}

	sprite_sys.set_parameters();
	gui_font.transform(math::matrix_identity());
	sprite_sys.get_renderer()->transform(math::matrix_identity());
	_root.draw(draw_event(point(0,0)));
	cur.draw();
}

void sge::gui::manager::move_mouse(const unit x, const unit y)
{
	cur.move(x,y);
	const mouse_move_event e(cur.pos(),mod_tracker.state());
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
