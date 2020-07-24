//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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

using
reference_tree
=
fcppt::container::tree::object<
	sge::gui::widget::reference
>;

}
}
}

#endif
