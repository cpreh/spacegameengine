//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/impl/extract_size.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/enumeration.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <sge/rucksack/widget/reference.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_comparison.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/algorithm/find_opt.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/math/dim/null.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::rucksack::widget::enumeration::enumeration(
	sge::rucksack::padding const &_padding
)
:
	sge::rucksack::widget::base(),
	padding_{
		_padding
	},
	children_(),
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
}

void
sge::rucksack::widget::enumeration::size(
	sge::rucksack::dim const &_size
)
{
	size_ =
		_size;
}

void
sge::rucksack::widget::enumeration::position(
	sge::rucksack::vector const &_position
)
{
	position_ =
		_position;
}

sge::rucksack::dim
sge::rucksack::widget::enumeration::size() const
{
	return
		size_;
}

sge::rucksack::vector
sge::rucksack::widget::enumeration::position() const
{
	return
		position_;
}

sge::rucksack::axis_policy2
sge::rucksack::widget::enumeration::axis_policy() const
{
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
}

void
sge::rucksack::widget::enumeration::relayout()
{
	sge::rucksack::vector current_pos(
		this->position().x(),
		this->position().y() + padding_.get()
	);

	sge::rucksack::scalar current_row_max_height{
		0
	};

	for(
		sge::rucksack::widget::reference const &child_ptr
		:
		children_
	)
	{
		sge::rucksack::dim const preferred_or_minimum{
			sge::rucksack::impl::extract_size(
				child_ptr.get().axis_policy().x()
			),
			sge::rucksack::impl::extract_size(
				child_ptr.get().axis_policy().y()
			)
		};

		// Next line
		if(
			current_pos.x() + padding_.get() + preferred_or_minimum.w()
			>
			this->position().x() + this->size().w()
		)
		{
			// This assertion makes sure that we have enough space
			// at the bottom. It's too strict, however, so I
			// uncommented it.
			//FCPPT_ASSERT_PRE(
			//	current_pos.y() + preferred_or_minimum.h() <= this->position().y() + this->size().h());
			current_pos.x() =
				this->position().x();

			current_pos.y() +=
				current_row_max_height + padding_.get();

			current_row_max_height =
				0;
		}

		child_ptr.get().position(
			sge::rucksack::vector{
				current_pos.x()
				+
				padding_.get()
				,
				current_pos.y()
			}
		);

		child_ptr.get().size(
			preferred_or_minimum
		);

		child_ptr.get().relayout();

		current_pos.x() +=
			preferred_or_minimum.w() + padding_.get();

		current_row_max_height =
			std::max(
				current_row_max_height,
				preferred_or_minimum.h()
			);
	}
}

void
sge::rucksack::widget::enumeration::push_back_child(
	sge::rucksack::widget::reference const _child
)
{
	children_.push_back(
		_child
	);

	_child.get().parent(
		sge::rucksack::widget::optional_ref{
			fcppt::reference_to_base<
				sge::rucksack::widget::base
			>(
				fcppt::make_ref(
					*this
				)
			)
		}
	);
}

sge::rucksack::widget::enumeration::~enumeration()
{
	for(
		sge::rucksack::widget::reference const &child_ptr
		:
		children_
	)
	{
		child_ptr.get().parent(
			sge::rucksack::widget::optional_ref()
		);
	}
}

void
sge::rucksack::widget::enumeration::child_destroyed(
	sge::rucksack::widget::base &_child
)
{
	children_.erase(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			fcppt::algorithm::find_opt(
				children_,
				fcppt::make_ref(
					_child
				)
			)
		)
	);
}
