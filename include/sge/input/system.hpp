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


#ifndef SGE_INPUT_SYSTEM_HPP_INCLUDED
#define SGE_INPUT_SYSTEM_HPP_INCLUDED

#include "callback.hpp"
#include "../window/instance_fwd.hpp"
#include "../signals/connection.hpp"
#include "../plugin/traits.hpp"
#include "../plugin/capabilities.hpp"
#include "../export.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace input
{

class SGE_CLASS_SYMBOL system : boost::noncopyable {
public:
	virtual signals::connection const
	register_callback(
		callback const &c) = 0;

	virtual signals::connection const
	register_repeat_callback(
		repeat_callback const &c) = 0;
	
	virtual void dispatch() = 0;

	virtual window::instance_ptr const window() const = 0;

	SGE_SYMBOL virtual ~system();
};

}

namespace plugin
{
namespace detail
{

template<> struct traits<input::system> {
	SGE_SYMBOL static address_name plugin_loader_name();
	SGE_SYMBOL static capabilities::type get_plugin_type();
	typedef input::system* (*loader_fun)(window::instance_ptr);
};

}
}

}

#endif
