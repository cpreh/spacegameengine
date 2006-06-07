#ifndef SGE_FONT_SYSTEM_HPP_INCLUDED
#define SGE_FONT_SYSTEM_HPP_INCLUDED

#include <locale>
#include "../main/shared_ptr.hpp"
#include "../renderer/texture.hpp"
#include "../renderer/font_types.hpp"
#include "../renderer/renderer.hpp"
#include "../math/rect.hpp"

namespace sge
{
	struct font_information {
		typedef basic_rect<space_unit> rect;
		struct position {
			position(const rect& r = rect(), const text_unit vshift = 0)
				: texture_pos(r), vshift(vshift) {}
			rect texture_pos;
			text_unit vshift;
		};
		typedef std::vector<position> position_vector;
		
		texture_ptr tex;
		position_vector positions;
		text_unit font_height;
	};

	class font_system {
	public:
		virtual ~font_system(){}
		virtual font_information create_font(renderer_ptr r, const std::string& name, bool italic, font_weight weight, text_unit height, const std::locale& loc = std::locale()) = 0;
	};

	typedef shared_ptr<font_system> font_system_ptr;
}

#endif

