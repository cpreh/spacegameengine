#ifndef SGE_GUI_LAYOUTS_VERTICAL_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_VERTICAL_HPP_INCLUDED

#include <sge/gui/layouts/row.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL vertical : public row
{
	public:
	SGE_SYMBOL vertical(widget &);
	private:
	std::size_t master() const { return static_cast<std::size_t>(1); }
};
}
}
}

#endif
