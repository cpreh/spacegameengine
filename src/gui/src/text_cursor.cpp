#include "../text_cursor.hpp"
#include "../skin.hpp"

sge::gui::text_cursor::text_cursor(sprite_system& s, const point pos, const dim sz, timer::interval_type blink_time)
: sprite(s,pos,sz,0,skin::textcursor_name),
  blink_timer(blink_time),
  visible(false)
{}

void sge::gui::text_cursor::draw()
{
	if(blink_timer.update())
		visible = !visible;
	if(visible)
		sprite::draw();
}
