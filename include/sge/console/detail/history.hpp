/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CONSOLE_DETAIL_HISTORY_HPP_INCLUDED
#define SGE_CONSOLE_DETAIL_HISTORY_HPP_INCLUDED

#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/math/dim/static.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/string.hpp>
#include <boost/range/iterator_range.hpp>
#include <deque>

namespace sge
{
namespace console
{
namespace detail
{

class history
{
public:
	typedef std::deque<
		fcppt::string
	> container;

	typedef container::iterator iterator;
	typedef container::const_iterator const_iterator;
	typedef container::const_reverse_iterator const_reverse_iterator;
	typedef boost::iterator_range<const_iterator> iterator_pair;
	typedef unsigned unit;
	typedef fcppt::math::box::rect<unit>::type rect;
	typedef fcppt::math::dim::static_<unit,2>::type dim;
	typedef fcppt::math::vector::static_<unit,2>::type point;

	history();

	iterator_pair const
	lines_inside(
		rect const &,
		unit height
	) const;

	void
	up();

	void
	down();

	void
	push_front(
		fcppt::string const &
	);

	void
	push_back(
		fcppt::string const &
	);

	fcppt::string const
	current() const;
private:
	container items_;
	iterator pos_;
};
}
}
}

#endif
