//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_TREE_HPP_INCLUDED
#define SGE_GUI_WIDGET_TREE_HPP_INCLUDED

#include <sge/gui/context_ref.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/reference_tree_vector.hpp>
#include <sge/gui/widget/tree_fwd.hpp>
#include <sge/gui/widget/unique_ptr_vector.hpp>
#include <fcppt/nonmovable.hpp>


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
	FCPPT_NONMOVABLE(
		tree
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	tree(
		sge::gui::context_ref,
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
