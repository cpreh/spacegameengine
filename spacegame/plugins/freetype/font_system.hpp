#ifndef SGE_FT_FONT_SYSTEM_HPP_INCLUDED
#define SGE_FT_FONT_SYSTEM_HPP_INCLUDED

#include "../../core/font/font_system.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

namespace sge
{
namespace ft
{

class font_system : public sge::font_system {
public:
	font_system();
	~font_system();
	font_information create_font(renderer_ptr r, const std::string& font_name, bool italic, font_weight weight, text_unit height, const std::locale& loc);
private:
	FT_Library library;
};

}
}

#endif

