/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/convert/from_gl_bool.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/config.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/context.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/optional_config.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::state::core::depth_stencil::stencil::context::context()
:
	sge::opengl::context::system::base(),
	config_(
		sge::opengl::convert::from_gl_bool(
			GLEW_VERSION_2_0
		)
		?
			sge::opengl::state::core::depth_stencil::stencil::optional_config(
				sge::opengl::state::core::depth_stencil::stencil::config(
					sge::opengl::deref_fun_ptr(
						glStencilFuncSeparate
					),
					sge::opengl::deref_fun_ptr(
						glStencilOpSeparate
					)
				)
			)
		:
			sge::opengl::state::core::depth_stencil::stencil::optional_config()
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::state::core::depth_stencil::stencil::context::~context()
{
}

sge::opengl::state::core::depth_stencil::stencil::optional_config const &
sge::opengl::state::core::depth_stencil::stencil::context::config() const
{
	return
		config_;
}

sge::opengl::context::system::id const
sge::opengl::state::core::depth_stencil::stencil::context::static_id(
	sge::opengl::context::system::make_id()
);
