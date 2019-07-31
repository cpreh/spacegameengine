//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GUI_WIDGET_REFERENCE_ALIGNMENT_PAIR_HPP_INCLUDED
#define SGE_GUI_WIDGET_REFERENCE_ALIGNMENT_PAIR_HPP_INCLUDED

#include <sge/gui/detail/symbol.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair_fwd.hpp>
#include <sge/rucksack/alignment.hpp>


namespace sge
{
namespace gui
{
namespace widget
{

class reference_alignment_pair
{
public:
	SGE_GUI_DETAIL_SYMBOL
	reference_alignment_pair(
		sge::gui::widget::reference,
		sge::rucksack::alignment
	);

	sge::gui::widget::reference
	reference() const;

	sge::rucksack::alignment
	alignment() const;
private:
	sge::gui::widget::reference reference_;

	sge::rucksack::alignment alignment_;
};

}
}
}

#endif
