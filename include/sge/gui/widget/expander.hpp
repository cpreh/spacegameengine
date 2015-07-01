#ifndef SGE_GUI_WIDGET_EXPANDER_HPP_INCLUDED
#define SGE_GUI_WIDGET_EXPANDER_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/widget/dummy.hpp>
#include <sge/gui/widget/expander_fwd.hpp>
#include <sge/rucksack/axis_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class expander
:
	public sge::gui::widget::dummy
{
	FCPPT_NONCOPYABLE(
		expander
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	explicit
	expander(
		sge::rucksack::axis
	);

	SGE_GUI_DETAIL_SYMBOL
	~expander()
	override;
private:
	sge::rucksack::widget::base &
	layout()
	override;

	sge::rucksack::widget::dummy layout_;
};

}
}
}

#endif
