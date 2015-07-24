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
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/enabled_visitor.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/visitor.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/write_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/off_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask_all.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::core::depth_stencil::stencil::visitor::visitor(
	sge::opengl::context::system::object &_system_context
)
:
	system_context_(
		_system_context
	)
{
}

sge::opengl::state::core::depth_stencil::stencil::visitor::result_type
sge::opengl::state::core::depth_stencil::stencil::visitor::operator()(
	sge::renderer::state::core::depth_stencil::stencil::off const &
) const
{
	return
		sge::opengl::state::core::depth_stencil::stencil::visitor::result_type{
			std::bind(
				sge::opengl::disable,
				GL_STENCIL_TEST
			),
			sge::opengl::state::core::depth_stencil::stencil::write_mask(
				sge::renderer::state::core::depth_stencil::stencil::write_mask_all()
			)
		};
}

sge::opengl::state::core::depth_stencil::stencil::visitor::result_type
sge::opengl::state::core::depth_stencil::stencil::visitor::operator()(
	sge::renderer::state::core::depth_stencil::stencil::enabled const &_enabled
) const
{
	return
		fcppt::algorithm::join(
			sge::opengl::state::core::depth_stencil::stencil::visitor::result_type{
				std::bind(
					sge::opengl::enable,
					GL_STENCIL_TEST
				)
			},
			fcppt::variant::apply_unary(
				sge::opengl::state::core::depth_stencil::stencil::enabled_visitor(
					system_context_,
					_enabled.ref(),
					_enabled.read_mask(),
					_enabled.write_mask()
				),
				_enabled.enabled_variant()
			)
		);
}
