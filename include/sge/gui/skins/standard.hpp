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
	SGE_SYMBOL void draw(widget const &,events::invalid_area const &);
	SGE_SYMBOL void draw(widgets::button const &,events::invalid_area const &);
	SGE_SYMBOL void draw(widgets::edit const &,events::invalid_area const &);
	SGE_SYMBOL void draw(widgets::label const &,events::invalid_area const &);
	SGE_SYMBOL dim const size_hint(widgets::button const &) const;
	SGE_SYMBOL dim const size_hint(widgets::edit const &) const;
	SGE_SYMBOL dim const size_hint(widgets::label const &) const;
	SGE_SYMBOL filesystem::path const cursor_path() const;
	private:
	color bgcolor,bgcolor_focused;
};
}
}
}

#endif
