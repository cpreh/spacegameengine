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


#include <sge/renderer/optional_matrix4.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/orthogonal_viewport.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/target/viewport_is_null.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>


sge::renderer::optional_matrix4
sge::renderer::projection::orthogonal_viewport(
	sge::renderer::target::viewport const &_viewport,
	sge::renderer::projection::near const _near,
	sge::renderer::projection::far const _far
)
{
	return
		sge::renderer::target::viewport_is_null(
			_viewport
		)
		?
			sge::renderer::optional_matrix4()
		:
			sge::renderer::optional_matrix4(
				sge::renderer::projection::orthogonal(
					sge::renderer::projection::rect(
						fcppt::math::vector::null<
							sge::renderer::projection::rect::vector
						>(),
						fcppt::math::dim::structure_cast<
							sge::renderer::projection::rect::dim,
							fcppt::cast::int_to_float_fun
						>(
							_viewport.get().size()
						)
					),
					_near,
					_far
				)
			)
		;
}
