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

#include <vector>
#include "../export.hpp"
#include "../shared_ptr.hpp"
#include "../types.hpp"
#include "../plugin_traits.hpp"
#include "../string.hpp"
#include "../window.hpp"
#include "adapter.hpp"
#include "renderer.hpp"

namespace sge
{

typedef std::vector<renderer_caps> renderer_caps_array;

struct renderer_parameters;

class renderer_system {
public:
	virtual const renderer_ptr
	create_renderer(
		const renderer_parameters& param,
		adapter_type adapter = 0,
		window_ptr wnd = window_ptr()) = 0;
	virtual const renderer_caps_array caps() const = 0;
	virtual ~renderer_system(){}
};

typedef shared_ptr<renderer_system> renderer_system_ptr;

namespace detail
{

template<> struct plugin_traits<renderer_system> {
	SGE_SYMBOL static address_name plugin_loader_name();
	SGE_SYMBOL static plugin_type::type get_plugin_type();
	typedef renderer_system* (*loader_fun)();
};

}

}

#endif
