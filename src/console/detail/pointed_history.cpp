/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/console/detail/pointed_history.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


sge::console::detail::pointed_history::pointed_history(
	size_type const _limit
)
:
	container_(),
	limit_(
		_limit
	),
	point_(
		0u
	)
{
	FCPPT_ASSERT_PRE(
		limit_
		>
		0u
	);
}

sge::console::detail::pointed_history::~pointed_history()
{
}

void
sge::console::detail::pointed_history::push_front(
	value_type const &_value
)
{
	container_.push_front(
		_value
	);

	if(
		container_.size()
		>
		limit_
	)
		container_.pop_back();
}

void
sge::console::detail::pointed_history::up()
{
	if(
		point_
		!=
		container_.size() - 1u
	)
		++point_;
}

void
sge::console::detail::pointed_history::down()
{
	if(
		point_
		!=
		0u
	)
		--point_;
}

void
sge::console::detail::pointed_history::to_begin()
{
	point_ =
		0u;
}

void
sge::console::detail::pointed_history::to_end()
{
	point_ =
		container_.size() - 1u;
}

sge::console::detail::pointed_history::const_iterator const
sge::console::detail::pointed_history::point() const
{
	return
		std::next(
			container_.begin(),
			static_cast<
				std::iterator_traits<
					const_iterator
				>::difference_type
			>(
				point_
			)
		);
}

sge::console::detail::pointed_history::const_iterator const
sge::console::detail::pointed_history::end() const
{
	return
		container_.end();
}
