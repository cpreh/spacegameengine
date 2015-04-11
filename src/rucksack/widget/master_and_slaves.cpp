/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <fcppt/maybe.hpp>


// TODO: Initialize position and size in the ctor?

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
		sge::rucksack::vector::null()
	},
	size_{
		sge::rucksack::dim::null()
	}
{
	surrounding_box_.push_back_child(
		enumeration_,
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

sge::rucksack::dim const
sge::rucksack::widget::master_and_slaves::size() const
{
	return
		size_;
}

sge::rucksack::vector const
sge::rucksack::widget::master_and_slaves::position() const
{
	return
		position_;
}

sge::rucksack::axis_policy2 const
sge::rucksack::widget::master_and_slaves::axis_policy() const
{
	return
		fcppt::maybe(
			master_pane_,
			[]{
				return
					sge::rucksack::axis_policy2{
						sge::rucksack::minimum_size{
							0
						},
						sge::rucksack::minimum_size{
							0
						}
					};
			},
			[](
				sge::rucksack::widget::base const &_master_pane
			)
			{
				return
					_master_pane.axis_policy();
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
	sge::rucksack::widget::base &_master_pane
)
{
	if(
		master_pane_.has_value()
	)
		surrounding_box_.pop_front_child();

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
	sge::rucksack::widget::base &_child
)
{
	enumeration_.push_back_child(
		_child
	);
}

sge::rucksack::widget::master_and_slaves::~master_and_slaves()
{
}
