#ifndef SGE_GUI_WIDGET_TREE_HPP_INCLUDED
#define SGE_GUI_WIDGET_TREE_HPP_INCLUDED

#include <sge/gui/context_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/reference_tree_vector.hpp>
#include <sge/gui/widget/tree_fwd.hpp>
#include <sge/gui/widget/unique_ptr_vector.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class tree
:
	public sge::gui::widget::box_container
{
	FCPPT_NONCOPYABLE(
		tree
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	tree(
		sge::gui::context &,
		sge::gui::widget::reference_tree_vector const &
	);

	SGE_GUI_DETAIL_SYMBOL
	~tree()
	override;
private:
	sge::gui::widget::unique_ptr_vector boxes_;
};

}
}
}

#endif
