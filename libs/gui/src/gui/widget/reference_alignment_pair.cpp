//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/rucksack/alignment.hpp>


sge::gui::widget::reference_alignment_pair::reference_alignment_pair(
	sge::gui::widget::reference const _reference,
	sge::rucksack::alignment const _alignment
)
:
	reference_(
		_reference
	),
	alignment_(
		_alignment
	)
{
}

sge::gui::widget::reference
sge::gui::widget::reference_alignment_pair::reference() const
{
	return
		reference_;
}

sge::rucksack::alignment
sge::gui::widget::reference_alignment_pair::alignment() const
{
	return
		alignment_;
}
