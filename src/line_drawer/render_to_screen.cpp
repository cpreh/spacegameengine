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


#include <sge/line_drawer/render_to_screen.hpp>
#include <sge/line_drawer/object.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/viewport_size.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>

void
sge::line_drawer::render_to_screen(
	sge::renderer::device &_renderer,
	object &_drawer)
{
	sge::renderer::scoped_transform projection_scope(
		_renderer,
		sge::renderer::matrix_mode::projection,
		sge::renderer::projection::orthogonal(
			sge::renderer::projection::rect(
				sge::renderer::projection::rect::vector::null(),
				fcppt::math::dim::structure_cast<
					sge::renderer::projection::rect::dim
				>(
					renderer::viewport_size(
						_renderer
					)
				)
			),
			sge::renderer::projection::near(
				0
			),
			sge::renderer::projection::far(
				10
			)
		)
	);

	sge::renderer::scoped_transform world_scope(
		_renderer,
		sge::renderer::matrix_mode::world,
		sge::renderer::matrix4::identity());

	_drawer.render();
}
