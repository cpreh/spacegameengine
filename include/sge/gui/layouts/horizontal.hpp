#ifndef SGE_GUI_LAYOUTS_HORIZONTAL_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_HORIZONTAL_HPP_INCLUDED

#include "row.hpp"
#include "../../export.hpp"

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL horizontal : public row
{
	public:
	SGE_SYMBOL horizontal(widgets::container &);
	private:
	std::size_t master() const { return static_cast<std::size_t>(0); }
};
}
}
}

#endif
