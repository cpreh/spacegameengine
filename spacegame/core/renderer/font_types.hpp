#ifndef SGE_FONT_TYPES_HPP_INCLUDED
#define SGE_FONT_TYPES_HPP_INCLUDED

#include <string>
#include "../main/types.hpp"
#include "./renderer_types.hpp"
#include "../math/vector2.hpp"
#include "../math/dim.hpp"

namespace sge
{

enum font_weight {
	FW_Thin, 
	FW_Normal,
	FW_Bold,
	FW_Heavy
};

enum text_flags {
	TXTF_AlignLeft    = 1,
	TXTF_AlignRight   = 1 << 1,
	TXTF_AlignHCenter = 1 << 2,
	TXTF_AlignTop     = 1 << 3,
	TXTF_AlignVCenter = 1 << 4,
	TXTF_AlignBottom  = 1 << 5,
	TXTF_NoMultiLine  = 1 << 6,
	TXTF_Default      = TXTF_AlignLeft | TXTF_AlignTop
};
typedef unsigned text_flag_t;

typedef space_unit text_unit;
typedef point text_pos;
typedef dim text_size;

struct font_parameters {
	font_parameters(const std::string& font_name, const bool italic = false,
	                const font_weight weight = FW_Normal, const text_unit height = 0.1f)
		: font_name(font_name), italic(italic),
		  weight(weight), height(height){}

	std::string    font_name;
	bool           italic;
	font_weight    weight;
	text_unit      height;
};

typedef char font_char;
typedef std::basic_string<font_char> font_string;

}

#endif
