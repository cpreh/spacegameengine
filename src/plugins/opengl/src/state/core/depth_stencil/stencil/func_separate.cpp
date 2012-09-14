/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/func_separate.hpp>
#include <sge/opengl/state/convert/stencil_func.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/func.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/tr1/functional.hpp>


sge::opengl::state::actor const
sge::opengl::state::core::depth_stencil::stencil::func_separate(
	GLenum const _side,
	sge::renderer::state::core::depth_stencil::stencil::func::type const _func,
	sge::renderer::state::core::depth_stencil::stencil::ref const _ref
)
{
	return
		sge::opengl::state::wrap_error_handler(
			std::tr1::bind(
				::glStencilFuncSeparate,
				_side,
				sge::opengl::state::convert::stencil_func(
					_func
				),
				static_cast<
					GLint
				>(
					_ref.get()
				),
				0u
			),
			FCPPT_TEXT("glStencilFuncSeparate")
		);
}
