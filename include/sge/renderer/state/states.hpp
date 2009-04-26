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



#ifndef SGE_RENDERER_STATE_STATES_HPP_INCLUDED
#define SGE_RENDERER_STATE_STATES_HPP_INCLUDED

#include <sge/export.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/types.hpp>

namespace sge
{
namespace renderer
{
namespace state
{

namespace cull_mode {
	enum type {
		off,
		back,
		front
	};
}

namespace depth_func
{
	enum type {
		off,
		never,
		less,
		equal,
		less_equal,
		greater,
		not_equal,
		greater_equal,
		always
	};
}

namespace stencil_func
{
	enum type {
		off,
		never,
		less,
		equal,
		less_equal,
		greater,
		not_equal,
		greater_equal,
		always
	};
}

namespace alpha_func
{
	enum type {
		off,
		never,
		less,
		equal,
		less_equal,
		greater,
		not_equal,
		greater_equal,
		always
	};
}

namespace fog_mode {
	enum type {
		off,
		linear,
		exp,
		exp2
	};
}

namespace draw_mode
{
	enum type {
		point,
		line,
		fill
	};
}

namespace source_blend_func
{
	enum type {
		zero,
		one,
		dest_color,
		inv_dest_color,
		src_alpha,
		inv_src_alpha,
		dest_alpha,
		inv_dest_alpha,
		src_alpha_sat
	};
}

namespace dest_blend_func
{
	enum type {
		zero,
		one,
		src_color,
		inv_src_color,
		src_alpha,
		inv_src_alpha,
		dest_alpha,
		inv_dest_alpha
	};
}

namespace int_ {
	typedef int_type base_type;
	typedef trampoline<base_type> trampoline_type;
	typedef var<base_type> type;

	SGE_SYMBOL extern trampoline_type const
		stencil_clear_val,
		stencil_ref;
}

namespace uint_ {
	typedef uint_type base_type;
	typedef trampoline<base_type> trampoline_type;
	typedef var<base_type> type;

	SGE_SYMBOL extern trampoline_type const
		stencil_mask;
}

namespace float_ {
	typedef float_type base_type;
	typedef trampoline<base_type> trampoline_type;
	typedef var<base_type> type;

	SGE_SYMBOL extern trampoline_type const
		zbuffer_clear_val,
		alpha_test_ref,
		fog_start,
		fog_end,
		fog_density;
}

namespace bool_ {
	typedef bool_type base_type;
	typedef trampoline<bool_type> trampoline_type;
	typedef var<base_type> type;

	SGE_SYMBOL extern trampoline_type const
		clear_zbuffer,
		clear_backbuffer,
		clear_stencil,
		enable_alpha_blending,
		enable_lighting;
}

namespace color_ {
	typedef color_type base_type;
	typedef var<base_type> type;
	typedef trampoline<base_type> trampoline_type;

	SGE_SYMBOL extern trampoline_type const
		clear_color,
		ambient_light_color,
		fog_color;
}

}
}
}

#endif
