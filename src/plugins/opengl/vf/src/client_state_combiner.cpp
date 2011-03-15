/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../context.hpp"
#include "../attribute_context.hpp"
#include "../enable_vertex_attrib_array.hpp"
#include "../disable_vertex_attrib_array.hpp"
#include "../../context/use.hpp"
#include <fcppt/container/linear_set_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/ref.hpp>
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
void
apply_difference(
	Set const &old_states,
	Set const &new_states,
	EnableFun,
	DisableFun
);

}

sge::opengl::vf::client_state_combiner::client_state_combiner(
	opengl::context::object &_context
)
:
	context_(
		opengl::context::use<
			vf::context
		>(
			_context
		)
	),
	attribute_context_(
		opengl::context::use<
			vf::attribute_context
		>(
			_context
		)
	),
	old_states_(
		context_.state()
	),
	new_states_(
		old_states_
	)
{}

void
sge::opengl::vf::client_state_combiner::enable(
	GLenum const _enum
)
{
	new_states_.enable(
		_enum
	);
}

void
sge::opengl::vf::client_state_combiner::disable(
	GLenum const _enum
)
{
	new_states_.disable(
		_enum
	);
}

void
sge::opengl::vf::client_state_combiner::enable_attribute(
	GLuint const _attribute
)
{
	new_states_.enable_attribute(
		_attribute
	);
}

void
sge::opengl::vf::client_state_combiner::disable_attribute(
	GLuint const _attribute
)
{
	new_states_.disable_attribute(
		_attribute
	);
}

sge::opengl::vf::client_state_combiner::~client_state_combiner()
{
	apply_difference(
		old_states_.normal_states(),
		new_states_.normal_states(),
		glEnableClientState,
		glDisableClientState
	);

	apply_difference(
		old_states_.attribute_states(),
		new_states_.attribute_states(),
		std::tr1::bind(
			vf::enable_vertex_attrib_array,
			fcppt::ref(
				attribute_context_
			),
			std::tr1::placeholders::_1
		),
		std::tr1::bind(
			vf::disable_vertex_attrib_array,
			fcppt::ref(
				attribute_context_
			),
			std::tr1::placeholders::_1
		)
	);

	context_.state(
		new_states_
	);
}

namespace
{

template<
	typename Set,
	typename EnableFun,
	typename DisableFun
>
void
apply_difference(
	Set const &old_states,
	Set const &new_states,
	EnableFun const enable,
	DisableFun const disable
)
{
	Set diff;

	std::set_difference(
		old_states.begin(),
		old_states.end(),
		new_states.begin(),
		new_states.end(),
		std::inserter(
			diff,
			diff.begin()
		)
	);

	BOOST_FOREACH(
		typename Set::const_reference r,
		diff
	)
		disable(r);

	diff.clear();

	std::set_difference(
		new_states.begin(),
		new_states.end(),
		old_states.begin(),
		old_states.end(),
		std::inserter(
			diff,
			diff.begin()
		)
	);

	BOOST_FOREACH(
		typename Set::const_reference r,
		diff
	)
		enable(r);
}

}
