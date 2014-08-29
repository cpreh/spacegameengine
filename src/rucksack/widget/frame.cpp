/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/axis_to_index.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/frame.hpp>
#include <sge/rucksack/widget/optional_parent.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/vector/fill.hpp>


sge::rucksack::widget::frame::frame(
	sge::rucksack::widget::base &_child,
	sge::rucksack::padding const _padding
)
:
	sge::rucksack::widget::base{
		sge::rucksack::widget::optional_parent(
			*this
		)
	},
	child_(
		_child
	),
	padding_{
		_padding
	}
{
}

void
sge::rucksack::widget::frame::size(
	sge::rucksack::dim const &_size
)
{
	child_.size(
		_size
		-
		this->extra_size()
	);
}

void
sge::rucksack::widget::frame::position(
	sge::rucksack::vector const &_position
)
{
	child_.position(
		_position
		+
		this->shifted_position()
	);
}

sge::rucksack::dim const
sge::rucksack::widget::frame::size() const
{
	return
		child_.size()
		+
		this->extra_size();
}

sge::rucksack::vector const
sge::rucksack::widget::frame::position() const
{
	return
		child_.position()
		-
		this->shifted_position();
}

sge::rucksack::axis_policy2 const
sge::rucksack::widget::frame::axis_policy() const
{
	auto const make_policy(
		[
			this
		](
			sge::rucksack::axis const _axis
		)
		{
			sge::rucksack::dim::size_type const index{
				sge::rucksack::axis_to_index(
					_axis
				)
			};

			sge::rucksack::axis_policy const policy(
				child_.axis_policy()[
					index
				]
			);

			return
				sge::rucksack::axis_policy{
					sge::rucksack::minimum_size(
						this->extra_size()[
							index
						]
					)
					+
					policy.minimum_size(),
					sge::rucksack::preferred_size(
						fcppt::optional_bind_construct(
							policy.preferred_size().get(),
							[
								this,
								index
							](
								sge::rucksack::scalar const _value
							)
							{
								return
									_value
									+
									this->extra_size()[
										index
									];
							}
						)
					),
					policy.is_expanding()
				};
		}
	);

	return
		sge::rucksack::axis_policy2(
			make_policy(
				sge::rucksack::axis::x
			),
			make_policy(
				sge::rucksack::axis::y
			)
		);
}

void
sge::rucksack::widget::frame::relayout()
{
	child_.relayout();
}

sge::rucksack::widget::frame::~frame()
{
}

sge::rucksack::vector const
sge::rucksack::widget::frame::shifted_position() const
{
	return
		fcppt::math::vector::fill<
			sge::rucksack::vector::dim_wrapper::value
		>(
			padding_.get()
		);
}

sge::rucksack::dim const
sge::rucksack::widget::frame::extra_size() const
{
	return
		fcppt::literal<
			sge::rucksack::scalar
		>(
			2
		)
		*
		fcppt::math::dim::fill<
			sge::rucksack::dim::dim_wrapper::value
		>(
			padding_.get()
		);
}

sge::rucksack::padding const
sge::rucksack::widget::frame::padding() const
{
	return
		padding_;
}
