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
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/math/matrix/orthogonal.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>

void
sge::line_drawer::render_to_screen(
	sge::renderer::device_ptr const renderer,
	object &drawer)
{
	sge::renderer::scoped_transform projection_scope(
		renderer,
		sge::renderer::matrix_mode::projection,
		fcppt::math::matrix::orthogonal(
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				renderer->onscreen_target()->viewport().get().w()),
			static_cast<sge::renderer::scalar>(
				renderer->onscreen_target()->viewport().get().h()),
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				10)));

	sge::renderer::scoped_transform world_scope(
		renderer,
		sge::renderer::matrix_mode::world,
		sge::renderer::matrix4::identity());

	drawer.render();
}
