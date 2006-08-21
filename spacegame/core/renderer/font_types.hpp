#ifndef SGE_FONT_TYPES_HPP_INCLUDED
#define SGE_FONT_TYPES_HPP_INCLUDED

#include <string>
#include "../main/types.hpp"
#include "./renderer_types.hpp"
#include "../math/vector2.hpp"
#include "../math/dim.hpp"
#include "../math/rect.hpp"

namespace sge
{

enum font_weight {
	FW_Thin, 
	FW_Normal,
	FW_Bold,
	FW_Heavy
};

enum font_flags {
	FTF_AlignLeft    = 1,
	FTF_AlignRight   = 1 << 1,
	FTF_AlignHCenter = 1 << 2,
	FTF_AlignTop     = 1 << 3,
	FTF_AlignVCenter = 1 << 4,
	FTF_AlignBottom  = 1 << 5,
	FTF_NoMultiLine  = 1 << 6,
	FTF_Default      = FTF_AlignLeft | FTF_AlignTop
};
typedef unsigned font_flag_t;

typedef space_unit font_unit;
typedef point font_pos;
typedef basic_dim<font_unit> font_size;
typedef basic_rect<font_unit> font_rect;
typedef char font_char;
typedef std::basic_string<font_char> font_string;

}

#endif
