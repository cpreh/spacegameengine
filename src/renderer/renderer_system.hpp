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


#ifndef SGE_RENDER_ERSYSTEM_HPP_INCLUDED
#define SGE_RENDER_ERSYSTEM_HPP_INCLUDED

#include <vector>
#include "../shared_ptr.hpp"
#include "../types.hpp"
#include "../plugin_traits.hpp"
#include "types.hpp"
#include "renderer.hpp"

namespace sge
{

typedef std::vector<renderer_caps> renderer_caps_array;

struct renderer_parameters {
	renderer_parameters(const display_mode& mode, bool windowed = false, multi_sample_type samples = 1, bool vsync = true);

	display_mode      mode;
	multi_sample_type samples;
	bool              windowed;
	bool              vsync;
};

class renderer_system {
public:
	virtual renderer_ptr create_renderer(const renderer_parameters& param,
	                                     int adapter = 0,
	                                     window_ptr wnd = window_ptr()) = 0;
	virtual const renderer_caps_array caps() const = 0;
	virtual ~renderer_system(){}
};

typedef shared_ptr<renderer_system> renderer_system_ptr;

namespace detail
{

template<> struct plugin_traits<renderer_system> {
	static const char* plugin_loader_name() { return "create_renderer_system"; }
	static plugin_type::type get_plugin_type() { return plugin_type::renderer; }
	typedef renderer_system* (*loader_fun)();
};

}

}

#endif
