/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_GUI_MAIN_AREA_SCREEN_CORNER_HPP_INCLUDED
#define SGE_GUI_MAIN_AREA_SCREEN_CORNER_HPP_INCLUDED

#include <sge/gui/context_fwd.hpp>
#include <sge/gui/gravity_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/main_area/viewport_adaptor.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/expander.hpp>
#include <sge/gui/widget/minimum_size.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace main_area
{

class screen_corner
:
	public sge::gui::main_area::base
{
	FCPPT_NONCOPYABLE(
		screen_corner
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	screen_corner(
		sge::renderer::device::core &,
		sge::viewport::manager &,
		sge::gui::context &,
		sge::gui::widget::base &,
		sge::gui::gravity
	);

	SGE_GUI_DETAIL_SYMBOL
	~screen_corner()
	override;

	SGE_GUI_DETAIL_SYMBOL
	void
	relayout()
	override;
private:
	sge::gui::widget::base &
	widget()
	override;

	sge::gui::widget::base &widget_;

	sge::gui::widget::minimum_size minimum_size_;

	sge::gui::widget::expander horizontal_expander_;

	sge::gui::widget::expander vertical_expander_;

	sge::gui::widget::box_container horizontal_container_;

	sge::gui::widget::box_container vertical_container_;

	sge::gui::main_area::viewport_adaptor viewport_adaptor_;
};

}
}
}

#endif
