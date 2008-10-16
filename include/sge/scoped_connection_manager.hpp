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


#ifndef SGE_SCOPED_CONNECTION_MANAGER_HPP_INCLUDED
#define SGE_SCOPED_CONNECTION_MANAGER_HPP_INCLUDED

#include "export.hpp"
#include "callback_connection.hpp"
#include "scoped_connection.hpp"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/noncopyable.hpp>

namespace sge
{

// TODO: we should use boost::signals::trackable instead
class SGE_CLASS_SYMBOL scoped_connection_manager : boost::noncopyable {
public:
	void connect(
		callback_connection const &);
private:
	typedef boost::ptr_vector<
		scoped_connection
	> connection_vector;

	connection_vector connections;
};

}

#endif
