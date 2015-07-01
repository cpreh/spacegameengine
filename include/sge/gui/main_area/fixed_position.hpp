#ifndef SGE_GUI_MAIN_AREA_FIXED_POSITION_HPP_INCLUDED
#define SGE_GUI_MAIN_AREA_FIXED_POSITION_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/minimum_size.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace main_area
{

class fixed_position
:
	public sge::gui::main_area::base
{
	FCPPT_NONCOPYABLE(
		fixed_position
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	fixed_position(
		sge::gui::widget::base &,
		sge::rucksack::vector
	);

	SGE_GUI_DETAIL_SYMBOL
	~fixed_position()
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
};

}
}
}

#endif
