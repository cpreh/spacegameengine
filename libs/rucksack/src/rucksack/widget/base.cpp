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


#include <sge/rucksack/access_axis.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/impl/update_axis.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/maybe_void.hpp>


void
sge::rucksack::widget::base::size(
	sge::rucksack::axis const _axis,
	sge::rucksack::scalar const _value
)
{
	this->size(
		sge::rucksack::impl::update_axis(
			this->size(),
			_axis,
			_value
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
		sge::rucksack::impl::update_axis(
			this->position(),
			_axis,
			_value
		)
	);
}

sge::rucksack::scalar
sge::rucksack::widget::base::size(
	sge::rucksack::axis const _axis
) const
{
	return
		sge::rucksack::access_axis(
			this->size(),
			_axis
		);
}

sge::rucksack::scalar
sge::rucksack::widget::base::position(
	sge::rucksack::axis const _axis
) const
{
	static_assert(
		sge::rucksack::vector::static_size::value
		==
		fcppt::enum_::size<
			sge::rucksack::axis
		>::value,
		""
	);

	return
		sge::rucksack::access_axis(
			this->position(),
			_axis
		);
}

sge::rucksack::widget::base::~base()
{
	fcppt::optional::maybe_void(
		parent_,
		[
			this
		](
			fcppt::reference<
				sge::rucksack::widget::base
			> const _parent
		)
		{
			_parent.get().child_destroyed(
				*this
			);
		}
	);
}

sge::rucksack::widget::base::base()
:
	parent_()
{
}

sge::rucksack::rect
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

sge::rucksack::widget::optional_ref
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
