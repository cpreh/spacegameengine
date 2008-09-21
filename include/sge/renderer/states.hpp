/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2008       Simon Stienen    (s.stienen@slashlife.org)

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


#ifndef SGE_RENDERER_STATES_HPP_INCLUDED
#define SGE_RENDERER_STATES_HPP_INCLUDED

#include "../export.hpp"
#include "any_color.hpp"
#include <boost/variant.hpp>
#include <set>

namespace sge
{
namespace renderer
{
namespace state
{

template<typename T>
struct traits;

template<>
struct traits<int> {
	enum available_states {
		stencil_clear_val
	};
};

template<>
struct traits<float> {
	enum available_states {
		zbuffer_clear_val,
		alpha_test_ref,
		fog_start,
		fog_end,
		fog_density
	};
};

template<>
struct traits<bool> {
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
struct traits<any_color> {
	enum available_states {
		clear_color,
		ambient_light_color,
		fog_color
	};
};

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

template<typename T>
struct var {
	typedef traits<T>::available_states state_type;
	typedef T value_type;

	SGE_SYMBOL var &operator=(
		value_type);
	
	SGE_SYMBOL state_type state() const;
	SGE_SYMBOL value_type value() const;

	SGE_SYMBOL explicit var(
		state_type state,
		value_type defval = value_type());
private:
	value_type val;
};

template<typename T>
struct trampoline {
	var<T> const operator=(T);
};

namespace int_state {
	typedef var<int> type;
	SGE_SYMBOL extern type
		stencil_clear_val;
}

namespace float_state {
	typedef var<float> type;
	SGE_SYMBOL extern type
		zbuffer_clear_val,
		alpha_test_ref,
		fog_start,
		fog_end,
		fog_density;
}

namespace bool_state {
	typedef var<bool> type;
	SGE_SYMBOL extern type
		clear_zbuffer,
		clear_backbuffer,
		clear_stencil,
		enable_alpha_blending,
		enable_lighting;
}

namespace color_state {
	typedef var<any_color> type;
	SGE_SYMBOL extern type
		clear_color,
		ambient_light_color,
		fog_color;
}

typedef boost::variant<
	int_state::type,
	float_state::type,
	bool_state::type,
	color_state::type,
	cull_mode::type,
	depth_func::type,
	stencil_func::type,
	alpha_func::type,
	fog_mode::type,
	draw_mode::type,
	source_blend_func::type,
	dest_blend_func::type
> any;


class list {
public:
	SGE_SYMBOL list();
	SGE_SYMBOL explicit list(
		any const &);
	SGE_SYMBOL list const operator()(
		any const &) const;

	SGE_SYMBOL void overwrite(
		any const &);

	template<typename T>
	T const get() const;

	typedef std::set<any> set_type;
	set_type const &values() const;
private:
	set_type set_;
};

list const combine(
	list,
	list const &);

}
}
}

#endif // SGE_RENDERER_STATES_HPP_INCLUDED
