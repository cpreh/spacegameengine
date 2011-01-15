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


#include "../program_holder.hpp"
#include "../programfuncs/create.hpp"
#include "../programfuncs/delete.hpp"
#include "../program_contexts.hpp"
#include "../instantiate.hpp"
#include "../../context/use.hpp"

template<
	typename Environment
>
sge::opengl::glsl::program_holder<Environment>::program_holder(
	opengl::context::object &_context
)
:
	context_(
		opengl::context::use<
			typename Environment::program_context
		>(
			_context
		)
	),
	id_(
		programfuncs::create<
			Environment
		>(
			context_
		)
	)
{
}

template<
	typename Environment
>
sge::opengl::glsl::program_holder<Environment>::~program_holder()
{
	programfuncs::delete_<
		Environment
	>(
		context_,
		id_
	);
}

template<
	typename Environment
>
typename sge::opengl::glsl::program_holder<Environment>::program_context const &
sge::opengl::glsl::program_holder<Environment>::context() const
{
	return context_;
}

template<
	typename Environment
>
typename sge::opengl::glsl::program_holder<Environment>::handle
sge::opengl::glsl::program_holder<Environment>::id() const
{
	return id_;
}

#define SGE_OPENGL_GLSL_INSTANTIATE_PROGRAM_HOLDER(\
	env\
)\
template class \
sge::opengl::glsl::program_holder<\
	env\
>;

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_INSTANTIATE_PROGRAM_HOLDER
)
