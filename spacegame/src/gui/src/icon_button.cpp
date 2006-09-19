#include "../icon_button.hpp"
#include "../manager.hpp"
#include "../skin.hpp"

sge::gui::icon_button::icon_button(manager& m, element* const parent, const point pos, const dim sz, const std::string& texture_released, const std::string& texture_hover, const std::string& texture_pressed, const bool visible, const bool enabled)
: rectangle(m,parent,pos,sz,texture_released,visible,enabled),
  texture_pressed(texture_pressed), texture_released(texture_released), texture_hover(texture_hover)
{}

void sge::gui::icon_button::on_draw(const draw_event& event)
{
	if(pressed())
		set_texture(texture_pressed);
	else if(m.hover()==this)
		set_texture(texture_hover);
	else
		set_texture(texture_released);
	rectangle::on_draw(event);
}
