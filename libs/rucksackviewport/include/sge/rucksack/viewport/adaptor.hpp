//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_VIEWPORT_ADAPTOR_HPP_INCLUDED
#define SGE_RUCKSACK_VIEWPORT_ADAPTOR_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/dim_fwd.hpp>
#include <sge/rucksack/vector_fwd.hpp>
#include <sge/rucksack/viewport/adaptor_fwd.hpp>
#include <sge/rucksack/viewport/detail/symbol.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge::rucksack::viewport
{
/**
 * The viewport adaptor has just one single child. It synchronizes the size and
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
class SGE_CORE_DETAIL_CLASS_SYMBOL adaptor
:
	public sge::rucksack::widget::base
{
	FCPPT_NONMOVABLE(
		adaptor
	);
public:
	// We need the renderer object for the size() and position() getters/setters.
	// The viewport manager ironically doesn't give us access to the viewport
	// directly.
	SGE_RUCKSACK_VIEWPORT_DETAIL_SYMBOL
	adaptor(
		sge::viewport::manager_ref,
		sge::renderer::device::core_ref
	);

	SGE_RUCKSACK_VIEWPORT_DETAIL_SYMBOL
	void
	size(
		sge::rucksack::dim const &
	)
	override;

	SGE_RUCKSACK_VIEWPORT_DETAIL_SYMBOL
	void
	position(
		sge::rucksack::vector const &
	)
	override;

	[[nodiscard]]
	SGE_RUCKSACK_VIEWPORT_DETAIL_SYMBOL
	sge::rucksack::dim
	size() const
	override;

	[[nodiscard]]
	SGE_RUCKSACK_VIEWPORT_DETAIL_SYMBOL
	sge::rucksack::vector
	position() const
	override;

	[[nodiscard]]
	SGE_RUCKSACK_VIEWPORT_DETAIL_SYMBOL
	sge::rucksack::axis_policy2
	axis_policy() const
	override;

	SGE_RUCKSACK_VIEWPORT_DETAIL_SYMBOL
	void
	relayout()
	override;

	SGE_RUCKSACK_VIEWPORT_DETAIL_SYMBOL
	void
	child(
		sge::rucksack::widget::reference
	);

	SGE_RUCKSACK_VIEWPORT_DETAIL_SYMBOL
	~adaptor()
	override;
private:
	sge::renderer::target::base &target_;

	sge::rucksack::widget::optional_ref child_;

	fcppt::signal::auto_connection const viewport_connection_;

	void
	manage_callback();

	void
	resize_child();

	void
	child_destroyed(
		sge::rucksack::widget::base & // NOLINT(google-runtime-references)
	)
	override;
};

}

#endif
