#ifndef SGE_GUI_CURSOR_HPP_INCLUDED
#define SGE_GUI_CURSOR_HPP_INCLUDED

#include "./types.hpp"
#include "../core/renderer/sprite.hpp"
#include <boost/utility.hpp>

namespace sge
{
namespace gui
{
	class manager;

	class cursor : sprite {
	public:
		cursor(manager& manager, point start, dim sz);
		void pressed(bool p);
		void move(unit dx, unit dy);
		void draw();
		using sprite::pos;
	private:
		point    mouse_min,
		         mouse_max;
		bool     is_pressed;
	};
}
}

#endif
