/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SCOPED_CONNECTION_HPP_INCLUDED
#define SGE_SCOPED_CONNECTION_HPP_INCLUDED

#include <boost/signals/connection.hpp>
#include <boost/ptr_container/ptr_map.hpp>

#include "callback_connection.hpp"

namespace sge
{

typedef boost::signals::scoped_connection scoped_connection;

class scoped_connection_manager {
public:
	typedef std::string key_type;

	scoped_connection_manager() {}
	~scoped_connection_manager() {}

	scoped_connection_manager(const scoped_connection_manager &) {} // NOOP
	scoped_connection_manager &operator=(const scoped_connection_manager &) { return *this; } // NOOP
	void scoped_connect(key_type, sge::callback_connection);
	key_type scoped_connect(sge::callback_connection);
	void scoped_disconnect(const key_type &);

private:
	typedef boost::ptr_map<key_type, scoped_connection> connection_map;
	unsigned anonymous_connections;
	connection_map cons;
};

}

#endif
