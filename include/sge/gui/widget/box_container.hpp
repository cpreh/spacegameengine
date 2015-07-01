#ifndef SGE_GUI_WIDGET_BOX_CONTAINER_HPP_INCLUDED
#define SGE_GUI_WIDGET_BOX_CONTAINER_HPP_INCLUDED

#include <sge/gui/context_fwd.hpp>
#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/widget/box_container_fwd.hpp>
#include <sge/gui/widget/container.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair_fwd.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/rucksack/alignment_fwd.hpp>
#include <sge/rucksack/axis_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/box.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class box_container
:
	public sge::gui::widget::container
{
	FCPPT_NONCOPYABLE(
		box_container
	);
public:
	SGE_GUI_DETAIL_SYMBOL
	box_container(
		sge::gui::context &,
		sge::gui::widget::reference_alignment_vector const &,
		sge::rucksack::axis
	);

	SGE_GUI_DETAIL_SYMBOL
	~box_container()
	override;

	SGE_GUI_DETAIL_SYMBOL
	void
	push_front(
		sge::gui::widget::reference_alignment_pair const &
	);

	SGE_GUI_DETAIL_SYMBOL
	void
	pop_front();

	SGE_GUI_DETAIL_SYMBOL
	void
	push_back(
		sge::gui::widget::reference_alignment_pair const &
	);

	SGE_GUI_DETAIL_SYMBOL
	void
	pop_back();

	SGE_GUI_DETAIL_SYMBOL
	void
	replace(
		sge::rucksack::widget::box::size_type,
		sge::gui::widget::reference_alignment_pair const &
	);

	SGE_GUI_DETAIL_SYMBOL
	void
	clear();

	sge::rucksack::widget::box &
	box_layout();
private:
	sge::rucksack::widget::box layout_;
};

}
}
}

#endif
