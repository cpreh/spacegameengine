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


#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/convert/to_gl_bool.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/wrap_error_handler.hpp>
#include <sge/opengl/state/convert/depth_func.hpp>
#include <sge/opengl/state/core/depth_stencil/depth/visitor.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/enable.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/off_fwd.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/tr1/functional.hpp>


sge::opengl::state::core::depth_stencil::depth::visitor::result_type const
sge::opengl::state::core::depth_stencil::depth::visitor::operator()(
	sge::renderer::state::core::depth_stencil::depth::off const &
) const
{
	return
		fcppt::assign::make_container<
			sge::opengl::state::core::depth_stencil::depth::visitor::result_type
		>(
			std::tr1::bind(
				sge::opengl::disable,
				GL_DEPTH_TEST
			)
		);
}

sge::opengl::state::core::depth_stencil::depth::visitor::result_type const
sge::opengl::state::core::depth_stencil::depth::visitor::operator()(
	sge::renderer::state::core::depth_stencil::depth::enable const &_enable
) const
{
	return
		fcppt::assign::make_container<
			sge::opengl::state::core::depth_stencil::depth::visitor::result_type
		>(
			std::tr1::bind(
				sge::opengl::enable,
				GL_DEPTH_TEST
			)
		)(
			sge::opengl::state::wrap_error_handler(
				std::tr1::bind(
					::glDepthFunc,
					sge::opengl::state::convert::depth_func(
						_enable.func()
					)
				),
				FCPPT_TEXT("glDepthFunc")
			)
		)(
			sge::opengl::state::wrap_error_handler(
				std::tr1::bind(
					::glDepthMask,
					sge::opengl::convert::to_gl_bool(
						_enable.write_enable().get()
					)
				),
				FCPPT_TEXT("glDepthMask")
			)
		);
}
