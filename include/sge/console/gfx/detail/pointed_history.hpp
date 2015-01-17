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


#ifndef SGE_CONSOLE_GFX_DETAIL_POINTED_HISTORY_HPP_INCLUDED
#define SGE_CONSOLE_GFX_DETAIL_POINTED_HISTORY_HPP_INCLUDED

#include <sge/font/string.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <deque>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace console
{
namespace gfx
{
namespace detail
{

class pointed_history
{
	FCPPT_NONCOPYABLE(
		pointed_history
	);
public:
	typedef
	sge::font::string
	value_type;

	typedef
	std::deque
	<
		value_type
	>
	container;

	typedef
	container::size_type
	size_type;

	typedef
	container::const_iterator
	const_iterator;

	explicit
	pointed_history(
		size_type limit
	);

	~pointed_history();

	void
	push_front(
		value_type const &
	);

	void
	up();

	void
	down();

	void
	to_begin();

	void
	to_end();

	const_iterator const
	point() const;

	const_iterator const
	end() const;
private:
	container container_;

	size_type limit_;

	size_type point_;
};

}
}
}
}

#endif
