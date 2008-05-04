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


#include <sge/renderer/renderer_states.hpp>
#include <sge/string.hpp>
#include <sge/iostream.hpp>
#include <ostream>

template<typename T>
sge::renderer_state_var<T> sge::renderer_state_var<T>::operator=(const T newval)
{
	renderer_state_var<T> cp(state_id, newval);
	val = cp.val;
	return cp;
}

template<typename T>
T sge::renderer_state_var<T>::value() const
{
	return val;
}

template<typename T>
sge::renderer_state_var<T>::renderer_state_var(
	const typename renderer_state_var_traits<T>::available_states state_id,
	const T defval)
: state_id(state_id),
  val(defval)
{}

template<typename T>
bool sge::renderer_state_var<T>::operator<(
	const renderer_state_var<T> &other) const
{
	return state_id < other.state_id;
}


sge::renderer_state_list::renderer_state_list()
{}

sge::renderer_state_list::renderer_state_list(
	any_renderer_state const &a)
{
	set_.insert(a);
}

sge::renderer_state_list sge::renderer_state_list::operator()(
	any_renderer_state const &a) const
{
	renderer_state_list temp(*this);
	if(!temp.set_.insert(a).second)
		sge::cerr << SGE_TEXT("warning: duplicate renderer state given!\n");
	return temp;
}

void sge::renderer_state_list::overwrite(
	any_renderer_state const& a)
{
	const set_type::iterator it(set_.find(a));
	if(it != set_.end())
		set_.erase(it);
	set_.insert(a);
	// TODO: is there a better way to do this?
}

sge::renderer_state_list::set_type const &
sge::renderer_state_list::get() const
{
	return set_;
}

template struct sge::renderer_state_var<int>;
template struct sge::renderer_state_var<float>;
template struct sge::renderer_state_var<bool>;
template struct sge::renderer_state_var<sge::color>;

template struct sge::renderer_state_var<sge::renderer_state_cull_mode_type::type>;
template struct sge::renderer_state_var<sge::renderer_state_depth_func_type::type>;
template struct sge::renderer_state_var<sge::renderer_state_stencil_func_type::type>;
template struct sge::renderer_state_var<sge::renderer_state_fog_mode_type::type>;
template struct sge::renderer_state_var<sge::renderer_state_draw_mode_type::type>;
template struct sge::renderer_state_var<sge::renderer_state_source_blend_func_type::type>;
template struct sge::renderer_state_var<sge::renderer_state_dest_blend_func_type::type>;

#undef STATE
#define STATE(STATE_, NAME_) \
	sge::STATE_::NAME_( \
		sge::renderer_state_var_traits<sge::STATE_::type::value_type>::NAME_\
	)

// singular states
#define SGE_RS_NAMESPACE_cull_mode         renderer_state_cull_mode_type
#define SGE_RS_NAMESPACE_depth_func        renderer_state_depth_func_type
#define SGE_RS_NAMESPACE_stencil_func      renderer_state_stencil_func_type
#define SGE_RS_NAMESPACE_fog_mode          renderer_state_fog_mode_type
#define SGE_RS_NAMESPACE_draw_mode         renderer_state_draw_mode_type
#define SGE_RS_NAMESPACE_source_blend_func renderer_state_source_blend_func_type
#define SGE_RS_NAMESPACE_dest_blend_func   renderer_state_dest_blend_func_type

#undef SSTATE
#define SSTATE(STATE_, NAME_) \
	sge::STATE_::NAME_( \
		sge::renderer_state_var_traits<sge::STATE_::type::value_type>::singular, \
		sge::SGE_RS_NAMESPACE_##STATE_::NAME_ \
	)



////////////////////////////////////////////////////////////////////////////////
// int_states
//

sge::int_state::type
	STATE(int_state, stencil_clear_val);



////////////////////////////////////////////////////////////////////////////////
// float_states
//

sge::float_state::type
	STATE(float_state, zbuffer_clear_val),
	STATE(float_state, fog_start),
	STATE(float_state, fog_end),
	STATE(float_state, fog_density);



////////////////////////////////////////////////////////////////////////////////
// bool_states
//

sge::bool_state::type
	STATE(bool_state, clear_zbuffer),
	STATE(bool_state, clear_backbuffer),
	STATE(bool_state, clear_stencil),
	STATE(bool_state, enable_alpha_blending),
	STATE(bool_state, enable_lighting);



////////////////////////////////////////////////////////////////////////////////
// color_states
//

sge::color_state::type
	STATE(color_state, clear_color),
	STATE(color_state, ambient_light_color),
	STATE(color_state, fog_color);



////////////////////////////////////////////////////////////////////////////////
// cull_modes
//

const sge::cull_mode::type
	SSTATE(cull_mode, off),
	SSTATE(cull_mode, back),
	SSTATE(cull_mode, front);



////////////////////////////////////////////////////////////////////////////////
// depth_funcs
//

const sge::depth_func::type
	SSTATE(depth_func, off),
	SSTATE(depth_func, never),
	SSTATE(depth_func, less),
	SSTATE(depth_func, equal),
	SSTATE(depth_func, less_equal),
	SSTATE(depth_func, greater),
	SSTATE(depth_func, not_equal),
	SSTATE(depth_func, greater_equal),
	SSTATE(depth_func, always);



////////////////////////////////////////////////////////////////////////////////
// stencil_funcs
//

const sge::stencil_func::type
	SSTATE(stencil_func, off),
	SSTATE(stencil_func, never),
	SSTATE(stencil_func, less),
	SSTATE(stencil_func, equal),
	SSTATE(stencil_func, less_equal),
	SSTATE(stencil_func, greater),
	SSTATE(stencil_func, not_equal),
	SSTATE(stencil_func, greater_equal),
	SSTATE(stencil_func, always);



////////////////////////////////////////////////////////////////////////////////
// fog_modes
//

const sge::fog_mode::type
	SSTATE(fog_mode, off),
	SSTATE(fog_mode, linear),
	SSTATE(fog_mode, exp),
	SSTATE(fog_mode, exp2);



////////////////////////////////////////////////////////////////////////////////
// draw_modes
//

const sge::draw_mode::type
	SSTATE(draw_mode, point),
	SSTATE(draw_mode, line),
	SSTATE(draw_mode, fill);



////////////////////////////////////////////////////////////////////////////////
// source_blend_funcs
//

const sge::source_blend_func::type
	SSTATE(source_blend_func, zero),
	SSTATE(source_blend_func, one),
	SSTATE(source_blend_func, dest_color),
	SSTATE(source_blend_func, inv_dest_color),
	SSTATE(source_blend_func, src_alpha),
	SSTATE(source_blend_func, inv_src_alpha),
	SSTATE(source_blend_func, dest_alpha),
	SSTATE(source_blend_func, inv_dest_alpha),
	SSTATE(source_blend_func, src_alpha_sat);



////////////////////////////////////////////////////////////////////////////////
// dest_blend_funcs
//

const sge::dest_blend_func::type
	SSTATE(dest_blend_func, zero),
	SSTATE(dest_blend_func, one),
	SSTATE(dest_blend_func, src_color),
	SSTATE(dest_blend_func, inv_src_color),
	SSTATE(dest_blend_func, src_alpha),
	SSTATE(dest_blend_func, inv_src_alpha),
	SSTATE(dest_blend_func, dest_alpha),
	SSTATE(dest_blend_func, inv_dest_alpha);
