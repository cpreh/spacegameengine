//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_UNIQUE_PTR_TREE_VECTOR_HPP_INCLUDED
#define SGE_GUI_WIDGET_UNIQUE_PTR_TREE_VECTOR_HPP_INCLUDED

#include <sge/gui/widget/unique_ptr_tree.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

typedef
std::vector<
	sge::gui::widget::unique_ptr_tree
>
unique_ptr_tree_vector;

}
}
}

#endif
