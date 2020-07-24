//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_WIDGET_DUMMY_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_DUMMY_HPP_INCLUDED

#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/detail/symbol.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace rucksack
{
namespace widget
{

class dummy
:
	public sge::rucksack::widget::base
{
	FCPPT_NONMOVABLE(
		dummy
	);
public:
	SGE_RUCKSACK_DETAIL_SYMBOL
	explicit
	dummy(
		sge::rucksack::axis_policy2 const &
	);

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	size(
		sge::rucksack::dim const &
	)
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	position(
		sge::rucksack::vector const &
	)
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	axis_policy(
		sge::rucksack::axis_policy2 const &
	);

	[[nodiscard]]
	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::dim
	size() const
	override;

	[[nodiscard]]
	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::vector
	position() const
	override;

	[[nodiscard]]
	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::axis_policy2
	axis_policy() const
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	relayout()
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	~dummy()
	override;
private:
	sge::rucksack::axis_policy2 axis_policy_;

	sge::rucksack::vector position_;

	sge::rucksack::dim size_;
};

}
}
}

#endif
