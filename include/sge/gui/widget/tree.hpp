/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
