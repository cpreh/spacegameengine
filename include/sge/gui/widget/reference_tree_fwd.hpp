#ifndef SGE_GUI_WIDGET_REFERENCE_TREE_FWD_HPP_INCLUDED
#define SGE_GUI_WIDGET_REFERENCE_TREE_FWD_HPP_INCLUDED

#include <sge/gui/widget/reference.hpp>
#include <fcppt/container/tree/object_fwd.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

typedef
fcppt::container::tree::object<
	sge::gui::widget::reference
>
reference_tree;

}
}
}

#endif
