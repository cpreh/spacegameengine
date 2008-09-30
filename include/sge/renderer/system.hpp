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


#ifndef SGE_RENDERER_SYSTEM_HPP_INCLUDED
#define SGE_RENDERER_SYSTEM_HPP_INCLUDED

#include "adapter.hpp"
#include "device_fwd.hpp"
#include "../export.hpp"
#include "../plugin/traits.hpp"
#include "../plugin/capabilities.hpp"
#include "../window_fwd.hpp"
#include <boost/noncopyable.hpp>
#include <vector>

namespace sge
{
namespace renderer
{

struct caps;

typedef std::vector<caps> caps_array;

struct parameters;

class SGE_CLASS_SYMBOL system : boost::noncopyable {
public:
	virtual device_ptr const
	create_renderer(
		parameters const &param,
		adapter_type adapter = 0,
		window_ptr wnd = window_ptr()) = 0;
	virtual caps_array const caps() const = 0;
	SGE_SYMBOL virtual ~system();
};

}

namespace plugin
{
namespace detail
{

template<> struct traits<renderer::system> {
	SGE_SYMBOL static address_name plugin_loader_name();
	SGE_SYMBOL static capabilities::type get_plugin_type();
	typedef renderer::system* (*loader_fun)();
};

}
}

}

#endif
