#ifndef SGE_GUI_UTILITY_BLIT_HPP_INCLUDED
#define SGE_GUI_UTILITY_BLIT_HPP_INCLUDED

#include <sge/gui/image_view.hpp>
#include <sge/gui/rect.hpp>

namespace sge
{
namespace gui
{
namespace utility
{
void blit_invalid(
	const_image_view const &,
	rect const &src_rect,
	image_view,
	rect const &invalid_rect,
	bool transparency = true);

void blit(
	const_image_view const &,
	rect const &src_rect,
	image_view,
	rect const &dst_rect,
	rect const &clip_rect);
}
}
}

#endif
