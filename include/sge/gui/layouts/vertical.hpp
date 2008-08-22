#ifndef SGE_GUI_LAYOUTS_VERTICAL_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_VERTICAL_HPP_INCLUDED

#include "row.hpp"
#include "../../export.hpp"

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL vertical : public row
{
	public:
	SGE_SYMBOL vertical(widgets::container &);
	private:
	dim::size_type master(dim const &) const { return static_cast<dim::size_type>(1); }
	point::size_type master(point const &) const { return static_cast<point::size_type>(1); }
};
}
}
}

#endif
