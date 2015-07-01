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
