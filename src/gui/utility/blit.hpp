#ifndef SGE_GUI_UTILITY_BLIT_HPP_INCLUDED
#define SGE_GUI_UTILITY_BLIT_HPP_INCLUDED

#include <sge/gui/types.hpp>

namespace sge
{
namespace gui
{
namespace utility
{
void blit(
	const_image_view const &,
	rect const &,
	image_view,
	rect const &);
}
}
}

#endif
