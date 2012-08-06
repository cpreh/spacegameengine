#ifndef SGE_RUCKSACK_WIDGET_BOX_BASE_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_BOX_BASE_HPP_INCLUDED

#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/aspect.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/class_symbol.hpp>
#include <sge/rucksack/symbol.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_parent.hpp>
#include <sge/rucksack/widget/box/child_information.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <list>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace rucksack
{
namespace widget
{
namespace box
{
/**
\brief Align child widgets next to each other in a box.
\details
The box class behaves just like the Qt box layout. It aligns its children
either vertically or horizontally (determined by the "axis" parameter which
specifies the "major axis" of alignment; hozirontal alignment has axis::x,
vertical has axis::y).
*/
class SGE_CLASS_SYMBOL base
:
	public sge::rucksack::widget::base
{
FCPPT_NONCOPYABLE(
	base);
public:
	SGE_RUCKSACK_SYMBOL
	base(
		sge::rucksack::axis::type,
		sge::rucksack::aspect const &);

	// Nothing fancy, just set the stored size (this should NOT cause a relayout
	// immediately)
	SGE_RUCKSACK_SYMBOL void
	size(
		sge::rucksack::dim const &);

	// Nothing fancy, just set the stored position (this should NOT cause a
	// relayout immediately)
	SGE_RUCKSACK_SYMBOL void
	position(
		sge::rucksack::vector const &);

	// Nothing fancy, just return the stored size
	SGE_RUCKSACK_SYMBOL sge::rucksack::dim const
	size() const;

	// Nothing fancy, just return the stored position
	SGE_RUCKSACK_SYMBOL sge::rucksack::vector const
	position() const;

	// We have to calculate/set:
	//
	// 1. The minimum size (for each axis)
	// 2. The preferred size (for each axis)
	// 3. If the widget is expandable (for each axis)
	// 4. Aspect
	//
	// The minimum size for the _major_ axis is easy: We just accumulate the
	// minimum sizes of all the children.
	//
	// The minimum size of the _minor_ axis is equally simple: Take the maximum
	// of all the children's sizes.
	//
	// For the preferred size, we forward to the minimum size if the preferred
	// size is not given. If it _is_ given, we do the same as in the minimum
	// case, just with "preferred" instead of "minimum".
	//
	// Finally, the widget is expandable on each axis if there's at least one
	// widget that's expandable.
	//
	// We just ignore the aspect for now. I have no use case for that, yet.
	//
	// Also note that currently, box widgets always have a preferred size (which
	// might be equal to the minimum size).
	SGE_RUCKSACK_SYMBOL sge::rucksack::axis_policy2 const
	axis_policy() const;

	// This does a lot of stuff, see the code itself.
	SGE_RUCKSACK_SYMBOL void
	relayout();

	SGE_RUCKSACK_SYMBOL void
	push_back_child(
		widget::base &,
		sge::rucksack::alignment::type);

	SGE_RUCKSACK_SYMBOL void
	push_front_child(
		widget::base &,
		sge::rucksack::alignment::type);

	SGE_RUCKSACK_SYMBOL void
	pop_front_child();


	SGE_RUCKSACK_SYMBOL ~base();
private:
	typedef
	std::list
	<
		std::pair<widget::base*,box::child_information>
	>
	child_information;

	child_information children_;
	// We use the axis_ to access the components of either a dim or a vector:
	//
	// v[axis_] = 10;
	//
	// So ideally, the data type for the axis is the data type operator[] takes.
	// This is dim::size_type (or vector::size_type, they're equivalent)
	sge::rucksack::dim::size_type const axis_;
	sge::rucksack::aspect const aspect_;
	sge::rucksack::vector position_;
	sge::rucksack::dim size_;

	// Those just return axis and (1-axis), but are better readable in the code
	sge::rucksack::dim::size_type
	major_axis() const;

	sge::rucksack::dim::size_type
	minor_axis() const;

	void
	relayout_major_axis();

	void
	relayout_minor_axis();

	void
	child_destroyed(
		widget::base &);

	box::child_information &
	information_for_ptr(
		widget::base const *);
};
}
}
}
}

#endif
