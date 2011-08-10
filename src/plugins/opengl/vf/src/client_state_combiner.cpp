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
#include <fcppt/tr1/functional.hpp>
#include <fcppt/ref.hpp>
#include <algorithm>
#include <iterator>

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
sge::opengl::vf::client_state_combiner::enable_texture(
	renderer::stage const _texture
)
{
	new_states_.enable_texture(
		_texture
	);
}

void
sge::opengl::vf::client_state_combiner::disable_texture(
	renderer::stage const _texture
)
{
	new_states_.disable_texture(
		_texture
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
		::glEnableClientState,
		::glDisableClientState
	);

	if(
		old_states_.texture_states().empty()
		&& !new_states_.texture_states().empty()
	)
		::glEnableClientState(
			GL_TEXTURE_COORD_ARRAY
		);
	else if(
		!old_states_.texture_states().empty()
		&& new_states_.texture_states().empty()
	)
		::glDisableClientState(
			GL_TEXTURE_COORD_ARRAY
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
	Set const &_old_states,
	Set const &_new_states,
	EnableFun const _enable,
	DisableFun const _disable
)
{
	Set diff;

	std::set_difference(
		_old_states.begin(),
		_old_states.end(),
		_new_states.begin(),
		_new_states.end(),
		std::inserter(
			diff,
			diff.begin()
		)
	);

	for(
		typename Set::const_iterator it(
			diff.begin()
		);
		it != diff.end();
		++it
	)
		_disable(
			*it
		);

	diff.clear();

	std::set_difference(
		_new_states.begin(),
		_new_states.end(),
		_old_states.begin(),
		_old_states.end(),
		std::inserter(
			diff,
			diff.begin()
		)
	);

	for(
		typename Set::const_iterator it(
			diff.begin()
		);
		it != diff.end();
		++it
	)
		_enable(
			*it
		);
}

}
