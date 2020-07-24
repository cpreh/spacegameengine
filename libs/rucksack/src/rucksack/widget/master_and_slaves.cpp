//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/padding_fwd.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/master_and_slaves.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/maybe.hpp>


// TODO(philipp): Initialize position and size in the ctor?

sge::rucksack::widget::master_and_slaves::master_and_slaves(
	sge::rucksack::padding const &_padding
)
:
	sge::rucksack::widget::base{},
	surrounding_box_{
		sge::rucksack::axis::x,
		sge::rucksack::padding{
			0
		}
	},
	master_pane_(),
	enumeration_{
		_padding
	},
	position_{
		fcppt::math::vector::null<
			sge::rucksack::vector
		>()
	},
	size_{
		fcppt::math::dim::null<
			sge::rucksack::dim
		>()
	}
{
	surrounding_box_.push_back_child(
		fcppt::reference_to_base<
			sge::rucksack::widget::base
		>(
			fcppt::make_ref(
				enumeration_
			)
		),
		sge::rucksack::alignment::center
	);
}

void
sge::rucksack::widget::master_and_slaves::size(
	sge::rucksack::dim const &_size
)
{
	size_ =
		_size;
}

void
sge::rucksack::widget::master_and_slaves::position(
	sge::rucksack::vector const &_position
)
{
	position_ =
		_position;
}

sge::rucksack::dim
sge::rucksack::widget::master_and_slaves::size() const
{
	return
		size_;
}

sge::rucksack::vector
sge::rucksack::widget::master_and_slaves::position() const
{
	return
		position_;
}

sge::rucksack::axis_policy2
sge::rucksack::widget::master_and_slaves::axis_policy() const
{
	return
		fcppt::optional::maybe(
			master_pane_,
			[]{
				return
					sge::rucksack::axis_policy2{
						sge::rucksack::axis_policy{
							sge::rucksack::minimum_size{
								0
							}
						},
						sge::rucksack::axis_policy{
							sge::rucksack::minimum_size{
								0
							}
						}
					};
			},
			[](
				fcppt::reference<
					sge::rucksack::widget::base
				> const _master_pane
			)
			{
				return
					_master_pane.get().axis_policy();
			}
		);
}

void
sge::rucksack::widget::master_and_slaves::relayout()
{
	surrounding_box_.position(
		this->position()
	);

	surrounding_box_.size(
		this->size()
	);

	surrounding_box_.relayout();
}

void
sge::rucksack::widget::master_and_slaves::master_pane(
	sge::rucksack::widget::reference const _master_pane
)
{
	if(
		master_pane_.has_value()
	)
	{
		surrounding_box_.pop_front_child();
	}

	surrounding_box_.push_front_child(
		_master_pane,
		sge::rucksack::alignment::center
	);

	master_pane_ =
		sge::rucksack::widget::optional_ref(
			_master_pane
		);
}

void
sge::rucksack::widget::master_and_slaves::push_back_child(
	sge::rucksack::widget::reference const _child
)
{
	enumeration_.push_back_child(
		_child
	);
}

sge::rucksack::widget::master_and_slaves::~master_and_slaves()
= default;
