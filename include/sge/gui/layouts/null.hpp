#ifndef SGE_GUI_LAYOUTS_NULL_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_NULL_HPP_INCLUDED

#include <sge/gui/layouts/base.hpp>
#include <sge/gui/export.hpp>

namespace sge
{
namespace gui
{
namespace layouts
{
class null : public base
{
	public:
	SGE_GUI_SYMBOL null();

	SGE_GUI_SYMBOL void compile(invalidation::type const &);
	SGE_GUI_SYMBOL void compile_static();
	SGE_GUI_SYMBOL void pos(point const &);
	SGE_GUI_SYMBOL void size(dim const &);
	SGE_GUI_SYMBOL dim const optimal_size() const;
};
}
}
}

#endif
