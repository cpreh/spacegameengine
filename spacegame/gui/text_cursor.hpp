#ifndef SGE_TEXT_CURSOR_HPP_INCLUDED
#define SGE_TEXT_CURSOR_HPP_INCLUDED

#include "../core/main/timer.hpp"
#include "../core/renderer/sprite.hpp"

namespace sge
{
	namespace gui
	{
		class text_cursor : sprite {
		public:
			text_cursor(sprite_system& s, point pos, dim sz, timer::interval_type blink_time);
			void draw();
			using sprite::width;
			using sprite::height;
			using sprite::pos;
		private:
			timer  blink_timer;
			bool   visible;
		};
	}
}

#endif
