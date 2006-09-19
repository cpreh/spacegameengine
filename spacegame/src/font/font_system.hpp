#ifndef SGE_FONT_SYSTEM_HPP_INCLUDED
#define SGE_FONT_SYSTEM_HPP_INCLUDED

#include <locale>
#include "../main/shared_ptr.hpp"
#include "../renderer/texture.hpp"
#include "../renderer/font_types.hpp"
#include "../renderer/renderer.hpp"
#include "../math/rect.hpp"
#include "./font_impl.hpp"

namespace sge
{

class font_system {
public:
	virtual ~font_system(){}
	virtual font_impl_ptr create_font(renderer_ptr r, const std::string& name, unsigned quality_in_pixel, font_weight weight) = 0;
};

typedef shared_ptr<font_system> font_system_ptr;

}

#endif

