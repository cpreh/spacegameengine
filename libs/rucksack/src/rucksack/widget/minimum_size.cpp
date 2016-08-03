/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/rucksack/axis_policy_function.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/make_axis_policy.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/minimum_size.hpp>
#include <sge/rucksack/impl/extract_size.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_to_base.hpp>


sge::rucksack::widget::minimum_size::minimum_size(
	sge::rucksack::widget::base &_child
)
:
	sge::rucksack::widget::base(),
	child_(
		_child
	)
{
	child_.parent(
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
	child_.position(
		_position
	);
}

sge::rucksack::dim
sge::rucksack::widget::minimum_size::size() const
{
	return
		child_.size();
}

sge::rucksack::vector
sge::rucksack::widget::minimum_size::position() const
{
	return
		child_.position();
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
									child_.axis_policy()[
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
		child_.axis_policy()
	);

	child_.size(
		sge::rucksack::dim(
			sge::rucksack::impl::extract_size(
				child_.axis_policy().x()
			),
			sge::rucksack::impl::extract_size(
				child_.axis_policy().y()
			)
		)
	);

	child_.relayout();
}

sge::rucksack::widget::minimum_size::~minimum_size()
{
}
