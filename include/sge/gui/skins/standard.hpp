#ifndef SGE_GUI_SKINS_STANDARD_HPP_INCLUDED
#define SGE_GUI_SKINS_STANDARD_HPP_INCLUDED

#include "../skin.hpp"
#include "../types.hpp"

namespace sge
{
namespace gui
{
namespace skins
{
class standard : public skin
{
	public:
	standard();
	void operator()(widgets::button &,events::invalid_area const &);
	private:
	color bgcolor,bgcolor_focused;
};
}
}
}

#endif
