#ifndef SGE_GUI_LAYOUTS_NULL_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_NULL_HPP_INCLUDED

#include "../layout.hpp"
#include "../../export.hpp"

namespace sge
{
namespace gui
{
namespace layouts
{
class null : public layout
{
	public:
	SGE_SYMBOL null(widget &);

	SGE_SYMBOL void update();
	SGE_SYMBOL void pos(point const &);
	SGE_SYMBOL void size(dim const &);
	SGE_SYMBOL dim const size_hint() const;
};
}
}
}

#endif
