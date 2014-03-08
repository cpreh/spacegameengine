/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/state/check_error.hpp>
#include <sge/opengl/state/index_actor.hpp>
#include <sge/opengl/state/index_actor_vector.hpp>
#include <sge/opengl/state/ffp/clip_plane/make_actors.hpp>
#include <sge/renderer/state/ffp/clip_plane/area.hpp>
#include <sge/renderer/state/ffp/clip_plane/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sge::opengl::state::index_actor_vector
sge::opengl::state::ffp::clip_plane::make_actors(
	sge::renderer::state::ffp::clip_plane::parameters const &_parameters
)
{
	typedef fcppt::math::vector::static_<
		GLdouble,
		4
	> vector4d;

	sge::renderer::state::ffp::clip_plane::area const area(
		_parameters.area()
	);

	return
		sge::opengl::state::index_actor_vector{
			sge::opengl::state::index_actor(
				[
					area
				](
					GLenum const _index
				)
				{
					::glClipPlane(
						_index,
						fcppt::math::vector::structure_cast<
							vector4d
						>(
							area.get()
						).data()
					);

					sge::opengl::state::check_error(
						FCPPT_TEXT("glClipPlane")
					);
				}
			)
		};
}
