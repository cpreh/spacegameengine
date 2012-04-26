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


#include <sge/line_drawer/object.hpp>
#include <sge/line_drawer/render_to_screen.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>


void
sge::line_drawer::render_to_screen(
	sge::renderer::context::object &_render_context,
	sge::line_drawer::object &_drawer)
{
	sge::renderer::scoped_transform const projection_scope(
		_render_context,
		sge::renderer::matrix_mode::projection,
		sge::renderer::projection::orthogonal(
			sge::renderer::projection::rect(
				sge::renderer::projection::rect::vector::null(),
				fcppt::math::dim::structure_cast<
					sge::renderer::projection::rect::dim
				>(
					sge::renderer::target::viewport_size(
						_render_context.target()
					)
				)
			),
			sge::renderer::projection::near(
				0.f
			),
			sge::renderer::projection::far(
				10.f
			)
		)
	);

	sge::renderer::scoped_transform const world_scope(
		_render_context,
		sge::renderer::matrix_mode::world,
		sge::renderer::matrix4::identity());

	_drawer.render(
		_render_context);
}
