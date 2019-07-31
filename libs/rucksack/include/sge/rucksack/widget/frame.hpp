//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_WIDGET_FRAME_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_FRAME_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/detail/symbol.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace rucksack
{
namespace widget
{

class SGE_CORE_DETAIL_CLASS_SYMBOL frame
:
	public sge::rucksack::widget::base
{
	FCPPT_NONCOPYABLE(
		frame
	);
public:
	SGE_RUCKSACK_DETAIL_SYMBOL
	frame(
		sge::rucksack::widget::base &,
		sge::rucksack::padding
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
	sge::rucksack::dim
	size() const
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::vector
	position() const
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::axis_policy2
	axis_policy() const
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	void
	relayout()
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	~frame()
	override;

	SGE_RUCKSACK_DETAIL_SYMBOL
	sge::rucksack::padding
	padding() const;
private:
	sge::rucksack::vector
	shifted_position() const;

	sge::rucksack::dim
	extra_size() const;

	sge::rucksack::widget::base &child_;

	sge::rucksack::padding const padding_;
};

}
}
}

#endif
