#include "../manager.hpp"
#include "../rectangle.hpp"

sge::gui::rectangle::rectangle(manager& m, element* const parent, const point pos, const dim sz, const std::string& tex, const bool visible, const bool enabled)
: element(m,parent,visible,true),
  sprite(m.get_sprite_system(),point(),sz,0,tex),
  rel_pos(pos)
{}

bool sge::gui::rectangle::intersects(const point p) const
{
	return sge::intersects(rect(x(),y(),x()+width(),y()+height()),p);
}

void sge::gui::rectangle::on_draw(const draw_event& e)
{
	sprite::pos(e.pos());
	sprite::draw();
}
