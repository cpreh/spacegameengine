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


#include "../attachment.hpp"
#include "../shader_base.hpp"
#include "../programfuncs/attach_shader.hpp"
#include "../programfuncs/detach_shader.hpp"
#include "../instantiate.hpp"
#include "../program_contexts.hpp"
#include <sge/renderer/glsl/shader.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>
#include <fcppt/shared_ptr_impl.hpp>

template<
	typename Environment
>
sge::opengl::glsl::attachment<Environment>::attachment(
	program_context const &_context,
	sge::renderer::glsl::shader_ptr const _shader,
	handle const _handle
)
:
	context_(
		_context
	),
	shader_(
		fcppt::dynamic_pointer_cast<
			shader_type
		>(
			_shader
		)
	),
	handle_(_handle)
{
	programfuncs::attach_shader<
		Environment
	>(
		_context,
		_handle,
		shader_->id()
	);
}

template<
	typename Environment
>
sge::opengl::glsl::attachment<Environment>::~attachment()
{
	programfuncs::detach_shader<
		Environment
	>(
		context_,
		handle_,
		shader_->id()
	);
}

#define SGE_OPENGL_GLSL_INSTANTIATE_ATTACHTMENT(\
	env\
)\
template class \
sge::opengl::glsl::attachment<\
	env\
>;

SGE_OPENGL_GLSL_INSTANTIATE(
	SGE_OPENGL_GLSL_INSTANTIATE_ATTACHTMENT
)
