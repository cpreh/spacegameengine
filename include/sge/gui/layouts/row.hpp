#ifndef SGE_GUI_LAYOUTS_ROW_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_ROW_HPP_INCLUDED

#include "../layout.hpp"
#include "../../export.hpp"

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL row : public layout
{
	public:
	SGE_SYMBOL row(widgets::container &);
	SGE_SYMBOL void update();
	SGE_SYMBOL dim const size_hint() const;
	private:
	// NOTE: this is actually quite hacky, I first tried to return a reference to
	// the w() or h() component, but then you get const issues which _might_ be
	// resolved somehow
	virtual dim::size_type master(dim const &) const = 0;
	dim::size_type slave(dim const &d) const { return master(d) == static_cast<dim::size_type>(0) ? static_cast<dim::size_type>(1) : static_cast<dim::size_type>(0); };

	virtual point::size_type master(point const &) const = 0;
	point::size_type slave(point const &d) const { return master(d) == static_cast<point::size_type>(0) ? static_cast<point::size_type>(1) : static_cast<point::size_type>(0); };
};
}
}
}

#endif
