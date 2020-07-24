//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/axis_policy_function.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/make_axis_policy.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/impl/extract_size.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/minimum_size.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>


sge::rucksack::widget::minimum_size::minimum_size(
	sge::rucksack::widget::reference const _child
)
:
	sge::rucksack::widget::base(),
	child_(
		_child
	)
{
	child_.get().parent(
		sge::rucksack::widget::optional_ref(
			fcppt::reference_to_base<
				sge::rucksack::widget::base
			>(
				fcppt::make_ref(
					*this
				)
			)
		)
	);
}

void
sge::rucksack::widget::minimum_size::size(
	sge::rucksack::dim const &
)
{
}

void
sge::rucksack::widget::minimum_size::position(
	sge::rucksack::vector const &_position
)
{
	child_.get().position(
		_position
	);
}

sge::rucksack::dim
sge::rucksack::widget::minimum_size::size() const
{
	return
		child_.get().size();
}

sge::rucksack::vector
sge::rucksack::widget::minimum_size::position() const
{
	return
		child_.get().position();
}

sge::rucksack::axis_policy2
sge::rucksack::widget::minimum_size::axis_policy() const
{
	return
		sge::rucksack::make_axis_policy(
			sge::rucksack::axis_policy_function{
				[
					this
				](
					sge::rucksack::axis const _axis
				)
				{
					return
						sge::rucksack::axis_policy{
							sge::rucksack::preferred_size{
								sge::rucksack::impl::extract_size(
									child_.get().axis_policy()[
										_axis
									]
								)
							}
						};
				}
			}
		);
}

void
sge::rucksack::widget::minimum_size::relayout()
{
	sge::rucksack::axis_policy2 const policy(
		child_.get().axis_policy()
	);

	child_.get().size(
		sge::rucksack::dim(
			sge::rucksack::impl::extract_size(
				policy.x()
			),
			sge::rucksack::impl::extract_size(
				policy.y()
			)
		)
	);

	child_.get().relayout();
}

sge::rucksack::widget::minimum_size::~minimum_size()
= default;
