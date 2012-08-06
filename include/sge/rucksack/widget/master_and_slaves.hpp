#ifndef SGE_RUCKSACK_WIDGET_MASTER_AND_SLAVES_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_MASTER_AND_SLAVES_HPP_INCLUDED

#include <sge/rucksack/padding.hpp>
#include <sge/class_symbol.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/enumeration.hpp>
#include <sge/rucksack/widget/box/base.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace rucksack
{
namespace widget
{
/**
 * The master and slaves widget is a pretty "special" one. Chances are you
 * don't need it.
 *
 * The widget has a "master widget" and multiple "subwidgets". The master
 * widget is displayed in a column on the left, the subwidgets are displayed on the right
 */
class SGE_CLASS_SYMBOL master_and_slaves
:
	public sge::rucksack::widget::base
{
FCPPT_NONCOPYABLE(
	master_and_slaves);
public:
	SGE_RUCKSACK_SYMBOL explicit
	master_and_slaves(
		sge::rucksack::padding const &);

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

	SGE_RUCKSACK_SYMBOL void
	master_pane(
		sge::rucksack::widget::base &);

	SGE_RUCKSACK_SYMBOL void
	push_back_child(
		sge::rucksack::widget::base &);

	SGE_RUCKSACK_SYMBOL ~master_and_slaves();
private:
	sge::rucksack::widget::box::base surrounding_box_;
	sge::rucksack::widget::base *master_pane_;
	sge::rucksack::widget::enumeration enumeration_;
	sge::rucksack::vector position_;
	sge::rucksack::dim size_;
};
}
}
}

#endif
