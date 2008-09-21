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


#include <sge/renderer/states.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <sge/iostream.hpp>
#include <boost/foreach.hpp>
#include <ostream>

template<typename T>
sge::renderer::state_var<T>
sge::renderer::state_var<T>::operator=(
	T const newval)
{
	return state_var<T>(newval);
}

template<typename T>
T sge::renderer::state_var<T>::value() const
{
	return val;
}

template<typename T>
sge::renderer::state_var<T>::state_var(
	T const defval)
: val(defval)
{}


sge::renderer::state_list::state_list()
{}

sge::renderer::state_list::state_list(
	any_state const &a)
{
	set_.insert(a);
}

const sge::renderer::state_list
sge::renderer::state_list::operator()(
	any_state const &a) const
{
	state_list temp(*this);
	if(!temp.set_.insert(a).second)
		sge::cerr << SGE_TEXT("warning: duplicate renderer state given!\n");
	return temp;
}

void sge::renderer::state_list::overwrite(
	any_state const& a)
{
	set_type::iterator const it(set_.find(a));
	if(it != set_.end())
		set_.erase(it);
	set_.insert(a);
	// TODO: is there a better way to do this?
}

template<typename T>
T const
sge::renderer::state_list::get() const
{
	BOOST_FOREACH(set_type::const_reference ref, set_)
		if(ref.type() == typeid(T))
			return boost::get<T>(ref);
	
	throw exception(
		SGE_TEXT("ogl::split_states::get(): state not found!"));
}

sge::renderer::state_list const
sge::renderer::combine(
	state_list l,
	state_list const &r)
{
	// FIXME
//	BOOST_FOREACH(renderer::any_state const &s, states.values())
//		l.overwrite(r.get_dynamic(s));
	return l;
}

template struct sge::renderer::state_var<int>;
template struct sge::renderer::state_var<float>;
template struct sge::renderer::state_var<bool>;
template struct sge::renderer::state_var<sge::renderer::any_color>;

#undef STATE
#define STATE(STATE_, NAME_) \
	sge::renderer::STATE_::NAME_( \
		sge::renderer::state_var_traits<sge::renderer::STATE_::type::value_type>::NAME_\
	)

// singular states
#define SGE_RS_NAMESPACE_cull_mode         state_cull_mode_type
#define SGE_RS_NAMESPACE_depth_func        state_depth_func_type
#define SGE_RS_NAMESPACE_stencil_func      state_stencil_func_type
#define SGE_RS_NAMESPACE_alpha_func        state_alpha_func_type
#define SGE_RS_NAMESPACE_fog_mode          state_fog_mode_type
#define SGE_RS_NAMESPACE_draw_mode         state_draw_mode_type
#define SGE_RS_NAMESPACE_source_blend_func state_source_blend_func_type
#define SGE_RS_NAMESPACE_dest_blend_func   state_dest_blend_func_type

#undef SSTATE
#define SSTATE(STATE_, NAME_) \
	sge::renderer::STATE_::NAME_( \
		sge::renderer::state_var_traits<sge::renderer::STATE_::type::value_type>::singular, \
		sge::renderer::SGE_RS_NAMESPACE_##STATE_::NAME_ \
	)



////////////////////////////////////////////////////////////////////////////////
// int_states
//

sge::renderer::int_state::type
	STATE(int_state, stencil_clear_val);



////////////////////////////////////////////////////////////////////////////////
// float_states
//

sge::renderer::float_state::type
	STATE(float_state, zbuffer_clear_val),
	STATE(float_state, alpha_test_ref),
	STATE(float_state, fog_start),
	STATE(float_state, fog_end),
	STATE(float_state, fog_density);



////////////////////////////////////////////////////////////////////////////////
// bool_states
//

sge::renderer::bool_state::type
	STATE(bool_state, clear_zbuffer),
	STATE(bool_state, clear_backbuffer),
	STATE(bool_state, clear_stencil),
	STATE(bool_state, enable_alpha_blending),
	STATE(bool_state, enable_lighting);



////////////////////////////////////////////////////////////////////////////////
// color_states
//

sge::renderer::color_state::type
	STATE(color_state, clear_color),
	STATE(color_state, ambient_light_color),
	STATE(color_state, fog_color);
