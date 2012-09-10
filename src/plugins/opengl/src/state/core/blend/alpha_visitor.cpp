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
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/convert/dest_blend_func.hpp>
#include <sge/opengl/state/convert/source_blend_func.hpp>
#include <sge/opengl/state/core/blend/alpha_visitor.hpp>
#include <sge/renderer/state/core/blend/combined.hpp>
#include <sge/renderer/state/core/blend/separate.hpp>


sge::opengl::state::core::blend::alpha_visitor::alpha_visitor(
	sge::opengl::context::system::object &_system_context
)
:
	system_context_(
		_system_context
	)
{
}

sge::opengl::state::core::blend::alpha_visitor::result_type const
sge::opengl::state::core::blend::alpha_visitor::operator()(
	sge::renderer::state::core::blend::combined const &_combined
) const
{
	return
		std::tr1::bind(
			::glBlendFunc,
			sge::opengl::state::convert::source_blend_func(
				_combined.source()
			),
			sge::opengl::state::convert::dest_blend_func(
				_combined.dest()
			)
		);
}

sge::opengl::state::core::blend::alpha_visitor::result_type const
sge::opengl::state::core::blend::alpha_visitor::operator()(
	sge::renderer::state::core::blend::separate const &_separate
) const
{
}
