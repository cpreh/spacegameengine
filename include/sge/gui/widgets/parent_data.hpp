#ifndef SGE_GUI_WIDGETS_PARENT_DATA_HPP_INCLUDED
#define SGE_GUI_WIDGETS_PARENT_DATA_HPP_INCLUDED

#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/manager.hpp>
#include <sge/gui/export.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class parent_data
{
public:
	SGE_GUI_SYMBOL parent_data(
		base &);
	SGE_GUI_SYMBOL parent_data(
		manager &);

	SGE_GUI_SYMBOL base *parent_widget() const;
	SGE_GUI_SYMBOL manager &parent_manager() const;
private:
	base *const widget_;
	manager &manager_;
};
}
}
}

#endif
