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


#include "../shader_base.hpp"
#include "../shaderfuncs/create.hpp"
#include "../shaderfuncs/delete.hpp"
#include "../instantiate.hpp"
#include "../shader_contexts.hpp"
#include "../../context/use.hpp"

template<
	typename Environment
>
sge::opengl::glsl::shader_base<Environment>::shader_base(
	opengl::context::object &_context,
	GLenum const _type
)
:
	context_(
		context::use<
			shader_context
		>(
			_context
		)
	),
	id_(
		shaderfuncs::create<
			Environment
		>(
			context_,
			_type
		)
	)
{}

template<
	typename Environment
>
typename sge::opengl::glsl::shader_base<Environment>::shader_context const &
sge::opengl::glsl::shader_base<Environment>::context() const
{
	return context_;
}

template<
	typename Environment
>
sge::opengl::glsl::shader_base<Environment>::~shader_base()
{
	shaderfuncs::delete_<
		Environment
	>(
		context_,
		id()
	);
}

template<
	typename Environment
>
typename sge::opengl::glsl::shader_base<Environment>::handle
sge::opengl::glsl::shader_base<Environment>::id() const
{
	return id_;
}

#define SGE_OPENGL_GLSL_INSTANTIATE_SHADER_BASE(\
	env\
)\
template class sge::opengl::glsl::shader_base<\
	env\
>;

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_INSTANTIATE_SHADER_BASE
)
