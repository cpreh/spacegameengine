#ifndef SGE_GUI_SKINS_STANDARD_HPP_INCLUDED
#define SGE_GUI_SKINS_STANDARD_HPP_INCLUDED

#include "../skin.hpp"
#include "../types.hpp"
#include "../../export.hpp"

namespace sge
{
namespace gui
{
namespace skins
{
class standard : public skin
{
	public:
	SGE_SYMBOL standard();
	SGE_SYMBOL void operator()(widgets::button &,events::invalid_area const &);
	private:
	color bgcolor,bgcolor_focused;
};
}
}
}

#endif
