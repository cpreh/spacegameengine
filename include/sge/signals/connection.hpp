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


#ifndef SGE_SIGNALS_CONNECTION_HPP_INCLUDED
#define SGE_SIGNALS_CONNECTION_HPP_INCLUDED

#include <boost/intrusive/list_hook.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/noncopyable.hpp>
#include <sge/auto_ptr.hpp>
#include <sge/scoped_ptr.hpp>
#include <sge/shared_ptr.hpp>

namespace sge
{
namespace signals
{

namespace detail
{

typedef boost::intrusive::list_base_hook<
	boost::intrusive::link_mode<
		boost::intrusive::auto_unlink
	>
> object_base_hook;

}

namespace detail
{
class connection : public object_base_hook, private boost::noncopyable
{
};
}

typedef auto_ptr<detail::connection> auto_connection;
typedef scoped_ptr<detail::connection> scoped_connection;
typedef shared_ptr<detail::connection> shared_connection;

}
}

#endif
