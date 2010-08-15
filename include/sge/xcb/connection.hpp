/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_XCB_CONNECTION_HPP_INCLUDED
#define SGE_XCB_CONNECTION_HPP_INCLUDED

#include <sge/xcb/connection_fwd.hpp>
#include <sge/xcb/screen_num.hpp>
#include <sge/xcb/string.hpp>
#include <sge/xcb/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <xcb/xcb.h>

namespace sge
{
namespace xcb
{

class connection
{
	FCPPT_NONCOPYABLE(connection)
public:
	SGE_XCB_SYMBOL
	connection();

	SGE_XCB_SYMBOL
	explicit connection(
		string const &display,
		xcb::screen_num
	);

	SGE_XCB_SYMBOL
	~connection();

	SGE_XCB_SYMBOL
	xcb_connection_t *
	get() const;

	SGE_XCB_SYMBOL
	xcb::screen_num const
	screen_num() const;
private:
	int screen_;

	xcb_connection_t *const connection_;
};

}
}

#endif
