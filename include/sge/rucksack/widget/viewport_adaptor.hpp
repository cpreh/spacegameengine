#ifndef SGE_RUCKSACK_WIDGET_VIEWPORT_ADAPTOR_HPP_INCLUDED
#define SGE_RUCKSACK_WIDGET_VIEWPORT_ADAPTOR_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/rucksack/symbol.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_parent.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace rucksack
{
namespace widget
{
/**
 * The viewport adaptor has juts one single child. It synchronizes the size and
 * position of this child with the given viewport. So in a hierarchy, this
 * manager is supposed to be near the top.
 *
 * The operations size(...) and position(...) resize and reposition the
 * viewport.
 *
 * Note that you _can_ use this class with a parent (in which case the viewport
 * will be changed by the parent) but I don't know any use case for this, since
 * a renderer can only have one viewport at a time.
 */
class SGE_CLASS_SYMBOL viewport_adaptor
:
	public sge::rucksack::widget::base
{
FCPPT_NONCOPYABLE(
	viewport_adaptor);
public:
	// We need the renderer object for the size() and position() getters/setters.
	// The viewport manager ironically doesn't give us access to the viewport
	// directly.
	SGE_RUCKSACK_SYMBOL explicit
	viewport_adaptor(
		sge::viewport::manager &,
		sge::renderer::device &);

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
	child(
		sge::rucksack::widget::base &);

	SGE_RUCKSACK_SYMBOL ~viewport_adaptor();
private:
	sge::renderer::device &renderer_;
	fcppt::signal::scoped_connection viewport_connection_;
	sge::rucksack::widget::base *child_;

	void
	manage_callback();

	void
	child_destroyed(
		sge::rucksack::widget::base &);
};
}
}
}

#endif
