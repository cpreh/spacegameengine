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
#include <sge/rucksack/axis_to_index.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <sge/src/rucksack/make_components.hpp>
#include <sge/src/rucksack/flip_axis.hpp>


void
sge::rucksack::widget::base::size(
	sge::rucksack::axis const _axis,
	sge::rucksack::scalar const _value
)
{
	this->size(
		sge::rucksack::make_components<
			sge::rucksack::dim
		>(
			std::make_pair(
				_axis,
				_value
			),
			std::make_pair(
				sge::rucksack::flip_axis(
					_axis
				),
				this->size(
					sge::rucksack::flip_axis(
						_axis
					)
				)
			)
		)
	);
}

void
sge::rucksack::widget::base::position(
	sge::rucksack::axis const _axis,
	sge::rucksack::scalar const _value
)
{
	this->position(
		sge::rucksack::make_components<
			sge::rucksack::vector
		>(
			std::make_pair(
				_axis,
				_value
			),
			std::make_pair(
				sge::rucksack::flip_axis(
					_axis
				),
				this->position(
					sge::rucksack::flip_axis(
						_axis
					)
				)
			)
		)
	);
}

sge::rucksack::scalar
sge::rucksack::widget::base::size(
	sge::rucksack::axis const _axis
) const
{
	return
		this->size()[
			sge::rucksack::axis_to_index(
				_axis
			)
		];
}

sge::rucksack::scalar
sge::rucksack::widget::base::position(
	sge::rucksack::axis const _axis
) const
{
	return
		this->position()[
			sge::rucksack::axis_to_index(
				_axis
			)
		];
}

sge::rucksack::widget::base::~base()
{
	if(
		parent_
	)
		parent_->child_destroyed(
			*this
		);
}

sge::rucksack::widget::base::base()
:
	parent_()
{
}

sge::rucksack::rect const
sge::rucksack::widget::base::area() const
{
	return
		sge::rucksack::rect{
			this->position(),
			this->size()
		};
}

void
sge::rucksack::widget::base::parent(
	sge::rucksack::widget::optional_ref const &_parent
)
{
	parent_ =
		_parent;
}

sge::rucksack::widget::optional_ref const
sge::rucksack::widget::base::parent() const
{
	return
		parent_;
}

void
sge::rucksack::widget::base::child_destroyed(
	sge::rucksack::widget::base &
)
{
}
