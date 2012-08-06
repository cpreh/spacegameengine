#ifndef SGE_RUCKSACK_WIDGET_DUMMY_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_DUMMY_HPP_INCLUDED

#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>

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
FCPPT_NONCOPYABLE(
	dummy);
public:
	SGE_RUCKSACK_SYMBOL explicit
	dummy(
		sge::rucksack::axis_policy2 const &);

	SGE_RUCKSACK_SYMBOL void
	size(
		sge::rucksack::dim const &);

	SGE_RUCKSACK_SYMBOL void
	position(
		sge::rucksack::vector const &);

	SGE_RUCKSACK_SYMBOL sge::rucksack::dim const
	size() const;

	SGE_RUCKSACK_SYMBOL sge::rucksack::vector const
	position() const;

	SGE_RUCKSACK_SYMBOL sge::rucksack::axis_policy2 const
	axis_policy() const;

	SGE_RUCKSACK_SYMBOL void
	relayout();

	SGE_RUCKSACK_SYMBOL
	~dummy();
private:
	sge::rucksack::axis_policy2 const axis_policy_;
	sge::rucksack::vector position_;
	sge::rucksack::dim size_;
};
}
}
}

#endif
