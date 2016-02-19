/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/state/core/depth_stencil/stencil/config.hpp>


sge::opengl::state::core::depth_stencil::stencil::config::config(
	gl_stencil_func_separate _stencil_func_separate,
	gl_stencil_op_separate _stencil_op_separate
)
:
	stencil_func_separate_(
		_stencil_func_separate
	),
	stencil_op_separate_(
		_stencil_op_separate
	)
{
}

sge::opengl::state::core::depth_stencil::stencil::config::gl_stencil_func_separate
sge::opengl::state::core::depth_stencil::stencil::config::stencil_func_separate() const
{
	return
		stencil_func_separate_;
}

sge::opengl::state::core::depth_stencil::stencil::config::gl_stencil_op_separate
sge::opengl::state::core::depth_stencil::stencil::config::stencil_op_separate() const
{
	return
		stencil_op_separate_;
}
