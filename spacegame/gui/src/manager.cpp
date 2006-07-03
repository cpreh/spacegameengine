#include "../../core/input/key_type.hpp"
#include "../manager.hpp"
#include "../skin.hpp"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <iostream>

sge::gui::manager::manager(const renderer_ptr rend, font& gui_font, const image_loader_ptr il, const std::string& graphics_path)
: graphics_path(graphics_path),
  sprite_sys(rend, boost::bind(&manager::on_texture_not_present, this, _1)),
  gui_font(gui_font),
  il(il),
  cur(*this,point(0.5f,0.5f),dim(0.025f,0.025f)),
  mouse_scale(0.01f,0.01f), 
  _focus(0),
  _hover(0),
  _pressed(0),
  _last_clicked(0),
  double_click_time(200),
  key_repeat_interval(50),
  key_repeat_time(500),
  mouse_repeat_interval(50),
  mouse_repeat_time(500),
  last_key(""),
  key_repeat(false),
  last_mouse(""),
  mouse_repeat(false),
  _root(*this)
{}

void sge::gui::manager::on_texture_not_present(const std::string& name)
{
	boost::filesystem::directory_iterator end;
	for(boost::filesystem::directory_iterator it(graphics_path); it != end; ++it)
		if(boost::filesystem::basename(*it) == name)
		{
			sprite_sys.add_texture(il->load_image(it->string()),name);
			return;
		}
	std::cerr << "Unable to find texture " << name << " for gui system!\n";
}

void sge::gui::manager::process(const input_array& v)
{
	const unit cursor_speed = 1;

	for(input_array::const_iterator it = v.begin(); it != v.end(); ++it)
	{
		const key_type& key = it->first;
		const key_code code = key.code;
		const bool val = it->second != 0 ? true : false;

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
			move_mouse(it->second * cursor_speed,0);
			break;
		case KC_MOUSEY:
			move_mouse(0,it->second * cursor_speed);
			break;
		default:
			if(is_mouse_key(code))
			{
				if(code==KC_MOUSEL)
					cur.pressed(val);

				const mouse_button_event e(cur.pos(),code,key_mod,val,key.char_code);
				if(val)
				{
					_root.mouse_down(e);
					if(last_mouse != key)
					{
						last_mouse = key;
						mouse_repeat = false;
						mouse_repeat_time.reset();
					}
				}
				else
				{
					_root.mouse_up(e);
					if(code==KC_MOUSEL)
						pressed(0);
					if(key==last_mouse)
					{
						mouse_repeat_time.reset();
						last_mouse.code = KC_DEFAULT;
						mouse_repeat = false;
					}
				}

				if(focus() == root())
					focus(0);
			}
			else if(is_keyboard_key(code))
			{
				const keyboard_button_event e(code,key_mod,val,key.char_code);
				if(!focus())
					break;
				
				if(val)
				{
					focus()->key_down(e);
					focus()->key_press(e);
					if(key != last_key)
					{
						last_key = key;
						key_repeat_time.reset();
						key_repeat = false;
					}
				}
				else
				{
					focus()->key_up(e);
					if(key == last_key)
					{
						last_key.code = KC_DEFAULT;
						key_repeat_time.reset();
						key_repeat = false;
					}
				}
			}
			break;
		}
	}

	// Repeat key if still down
	if(focus())
	{
		if(!mouse_repeat)
		{
			if(last_mouse.code != KC_DEFAULT)
			{
				if(mouse_repeat_time.update())
					mouse_repeat = true;
			}
			else
				mouse_repeat_time.reset();
		}
		else
			if(mouse_repeat_interval.update())
				focus()->mouse_press(mouse_button_event(cur.pos(),last_mouse.code,key_mod,true,last_mouse.char_code));

		if(!key_repeat)
		{
			if(last_key.code != KC_DEFAULT)
			{
				if(key_repeat_time.update())
					key_repeat = true;
			}
			else
				key_repeat_time.reset();
		}
		else
			if(key_repeat_interval.update())
				focus()->key_press(keyboard_button_event(last_key.code,key_mod,true,last_key.char_code));
	}

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

void sge::gui::manager::draw_selection(const point p, const dim sz)
{

}
