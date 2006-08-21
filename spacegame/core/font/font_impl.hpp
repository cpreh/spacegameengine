#ifndef SGE_FONT_IMPL_HPP_INCLUDED
#define SGE_FONT_IMPL_HPP_INCLUDED

#include "../main/shared_ptr.hpp"
#include "../renderer/font_types.hpp"
#include "../renderer/texture.hpp"

namespace sge
{

struct font_char_rect {
	font_rect rect;
	texture_ptr tex;
	font_unit top;
};

class font_impl {
public:
	virtual ~font_impl(){}
	virtual font_char_rect load_char(font_char c) = 0;
	virtual unsigned optimal_height_base() const = 0;
};

typedef shared_ptr<font_impl> font_impl_ptr;

}

#endif
