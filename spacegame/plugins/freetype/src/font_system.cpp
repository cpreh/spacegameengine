#include "../font_system.hpp"
#include "../font_impl.hpp"

sge::font_impl_ptr sge::ft::font_system::create_font(const renderer_ptr r, const std::string& font_name, const font_weight weight)
{
	return font_impl_ptr(new font_impl(_library, r, font_name, weight));
}
