#ifndef SGE_GUI_WIDGET_PREFERRED_SIZE_HPP_INCLUDED
#define SGE_GUI_WIDGET_PREFERRED_SIZE_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/widget/dummy.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class preferred_size
:
	public sge::gui::widget::dummy
{
	FCPPT_NONCOPYABLE(
		preferred_size
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	explicit
	preferred_size(
		sge::rucksack::dim const &
	);

	SGE_GUI_DETAIL_SYMBOL
	~preferred_size()
	override;

	sge::rucksack::widget::base &
	layout()
	override;
private:
	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif

