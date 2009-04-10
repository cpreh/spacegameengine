#ifndef SGE_GUI_LAYOUTS_HORIZONTAL_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_HORIZONTAL_HPP_INCLUDED

#include <sge/gui/layouts/row.hpp>
#include <sge/gui/export.hpp>

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL horizontal : public row
{
	public:
	SGE_GUI_SYMBOL horizontal(
		widget &);
	private:
	dim::const_reference master(
		dim const &) const;
	dim::reference master(
		dim &) const;
	point::const_reference master(
		point const &) const;
	point::reference master(
		point &) const;
};
}
}
}

#endif
