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


#include "../client_state_combiner.hpp"
#include "../global_client_state.hpp"
#include "../vertex_attrib.hpp"
#include <sge/container/linear_set_impl.hpp>
#include <boost/foreach.hpp>
#include <functional>
#include <algorithm>

namespace
{

template<
	typename Set,
	typename EnableFun,
	typename DisableFun
>
void apply_difference(
	Set const &old_states,
	Set const &new_states,
	EnableFun,
	DisableFun);

}

sge::ogl::vf::client_state_combiner::client_state_combiner(
	client_state const &old_states)
:
	old_states(old_states)
{}

void sge::ogl::vf::client_state_combiner::enable(
	GLenum const e)
{
	new_states.enable(e);
}

void sge::ogl::vf::client_state_combiner::enable_attribute(
	GLuint const i)
{
	new_states.enable_attribute(i);
}

sge::ogl::vf::client_state_combiner::~client_state_combiner()
{
	apply_difference(
		old_states.normal_states(),
		new_states.normal_states(),
		glEnableClientState,
		glDisableClientState);
	
	apply_difference(
		old_states.attribute_states(),
		new_states.attribute_states(),
		enable_vertex_attrib_array,
		disable_vertex_attrib_array);

	global_client_state(
		new_states);
}

namespace
{

template<
	typename Set,
	typename EnableFun,
	typename DisableFun
>
void apply_difference(
	Set const &old_states,
	Set const &new_states,
	EnableFun const enable,
	DisableFun const disable)
{
	Set diff;
	std::set_difference(
		old_states.begin(),
		old_states.end(),
		new_states.begin(),
		new_states.end(),
		std::inserter(
			diff,
			diff.begin()));
	
	BOOST_FOREACH(typename Set::const_reference r, diff)
		disable(r);
	
	diff.clear();

	std::set_difference(
		new_states.begin(),
		new_states.end(),
		old_states.begin(),
		old_states.end(),
		std::inserter(
			diff,
			diff.begin()));
	
	BOOST_FOREACH(typename Set::const_reference r, diff)
		enable(r);
}

}
