#include "../cursor.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::cursor::cursor(manager& m, point start, dim sz)
: sprite(m.get_sprite_system(),start,sz,0,skin::cursor_name),
  mouse_min(0,0),
  mouse_max(1,1),
  is_pressed(false)
{}

void sge::gui::cursor::pressed(const bool p)
{
	is_pressed = p;
}

void sge::gui::cursor::move(const unit dx, const unit dy)
{
	point p = sprite::pos();
	p.x += dx;
	p.y += dy;
	p.x = std::min(p.x,mouse_max.x);
	p.x = std::max(p.x,mouse_min.x);
	p.y = std::min(p.y,mouse_max.y);
	p.y = std::max(p.y,mouse_min.y);
	sprite::pos(p);
}

void sge::gui::cursor::draw()
{
	set_texture(is_pressed ? skin::cursor_name : skin::cursor_pressed_name);
	sprite::draw();
}

