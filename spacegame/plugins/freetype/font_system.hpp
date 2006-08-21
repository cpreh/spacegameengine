#ifndef SGE_FT_FONT_SYSTEM_HPP_INCLUDED
#define SGE_FT_FONT_SYSTEM_HPP_INCLUDED

#include "../../core/font/font_system.hpp"
#include "../../core/font/font_impl.hpp"
#include "./library.hpp"

namespace sge
{
namespace ft
{

class font_system : public sge::font_system {
public:
	font_impl_ptr create_font(renderer_ptr r, const std::string& font_name, font_weight weight);
private:
	library _library;
};

}
}

#endif

