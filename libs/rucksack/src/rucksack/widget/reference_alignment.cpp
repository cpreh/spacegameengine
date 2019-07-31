//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <sge/rucksack/widget/reference_alignment.hpp>


sge::rucksack::widget::reference_alignment::reference_alignment(
	sge::rucksack::widget::reference const _reference,
	sge::rucksack::alignment const _alignment
)
:
	reference_{
		_reference
	},
	alignment_{
		_alignment
	}
{
}

sge::rucksack::widget::reference
sge::rucksack::widget::reference_alignment::reference() const
{
	return
		reference_;
}

sge::rucksack::alignment
sge::rucksack::widget::reference_alignment::alignment() const
{
	return
		alignment_;
}
