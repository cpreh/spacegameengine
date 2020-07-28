//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/state/check_error.hpp>
#include <sge/opengl/state/index_actor.hpp>
#include <sge/opengl/state/index_actor_vector.hpp>
#include <sge/opengl/state/ffp/clip_plane/make_actors.hpp>
#include <sge/renderer/state/ffp/clip_plane/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sge::opengl::state::index_actor_vector
sge::opengl::state::ffp::clip_plane::make_actors(
	sge::renderer::state::ffp::clip_plane::parameters const &_parameters
)
{
	using
	vector4d
	=
	fcppt::math::vector::static_<
		GLdouble,
		4
	>;

	return
		sge::opengl::state::index_actor_vector{
			sge::opengl::state::index_actor(
				[
					area =
						_parameters.area()
				](
					GLenum const _index
				)
				{
					auto const gl_vec(
						fcppt::math::vector::structure_cast<
							vector4d,
							fcppt::cast::size_fun
						>(
							area.get()
						)
					);

					sge::opengl::call(
						::glClipPlane,
						_index,
						gl_vec.storage().data()
					);

					sge::opengl::state::check_error(
						FCPPT_TEXT("glClipPlane")
					);
				}
			)
		};
}
