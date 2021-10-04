//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_WIDGET_REFERENCE_ALIGNMENT_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_REFERENCE_ALIGNMENT_HPP_INCLUDED

#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/detail/symbol.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <sge/rucksack/widget/reference_alignment_fwd.hpp>


namespace sge::rucksack::widget
{

class reference_alignment
{
public:
	SGE_RUCKSACK_DETAIL_SYMBOL
	reference_alignment(
		sge::rucksack::widget::reference,
		sge::rucksack::alignment
	);

	[[nodiscard]]
	sge::rucksack::widget::reference
	reference() const;

	[[nodiscard]]
	sge::rucksack::alignment
	alignment() const;
private:
	sge::rucksack::widget::reference reference_;

	sge::rucksack::alignment alignment_;
};

}

#endif
