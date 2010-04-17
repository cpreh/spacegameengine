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


#ifndef SGE_XCB_SCREEN_ITERATOR_HPP_INCLUDED
#define SGE_XCB_SCREEN_ITERATOR_HPP_INCLUDED

#include <sge/xcb/setup_fwd.hpp>
#include <sge/xcb/screen.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <xcb/xcb.h>
#include <iterator>

namespace sge
{
namespace xcb
{

class screen_iterator
:
	public boost::iterator_facade<
		screen_iterator,
		screen,
		std::forward_iterator_tag,
		screen
	>	
{
public:
	screen_iterator();

	explicit screen_iterator(
		setup const &
	);
private:
	reference
	dereference() const;

	void
	increment();

	bool
	equal_to(
		screen_iterator const &
	) const;

	xcb_screen_iterator_t iterator_;

	friend class boost::iterator_core_access;
};

}
}

#endif
