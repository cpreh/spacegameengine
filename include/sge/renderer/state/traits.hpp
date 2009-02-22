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


#ifndef SGE_RENDERER_STATE_TRAITS_HPP_INCLUDED
#define SGE_RENDERER_STATE_TRAITS_HPP_INCLUDED

#include <sge/renderer/state/types.hpp>

namespace sge
{
namespace renderer
{
namespace state
{

template<typename T>
struct traits;

template<>
struct traits<int_type> {
	enum available_states {
		stencil_clear_val,
		stencil_ref
	};
};

template<>
struct traits<uint_type> {
	enum available_states {
		stencil_mask
	};
};

template<>
struct traits<float_type> {
	enum available_states {
		zbuffer_clear_val,
		alpha_test_ref,
		fog_start,
		fog_end,
		fog_density
	};
};

template<>
struct traits<bool_type> {
	enum available_states {
		clear_zbuffer,
		clear_backbuffer,
		clear_stencil,
		enable_alpha_blending,
		enable_alpha_test,
		enable_lighting
	};
};

template<>
struct traits<color_type> {
	enum available_states {
		clear_color,
		ambient_light_color,
		fog_color
	};
};

}
}
}

#endif
