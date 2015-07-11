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


#ifndef SGE_GUI_MAIN_AREA_VIEWPORT_ADAPTOR_HPP_INCLUDED
#define SGE_GUI_MAIN_AREA_VIEWPORT_ADAPTOR_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/rucksack/viewport/adaptor.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace main_area
{

class viewport_adaptor
:
	public sge::gui::main_area::base
{
	FCPPT_NONCOPYABLE(
		viewport_adaptor
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	viewport_adaptor(
		sge::renderer::device::core &,
		sge::viewport::manager &,
		sge::gui::widget::base &
	);

	SGE_GUI_DETAIL_SYMBOL
	~viewport_adaptor()
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

	sge::rucksack::viewport::adaptor impl_;
};

}
}
}

#endif
