//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/set_array.hpp>
#include <sge/opengl/state/convert/light_index.hpp>
#include <sge/opengl/state/ffp/lighting/light/context.hpp>
#include <sge/opengl/state/ffp/lighting/light/object.hpp>
#include <sge/opengl/state/ffp/lighting/light/set.hpp>
#include <sge/renderer/state/ffp/lighting/light/const_object_ref_vector.hpp>
#include <fcppt/make_ref.hpp>


void
sge::opengl::state::ffp::lighting::light::set(
	sge::opengl::context::object &_context,
	sge::renderer::state::ffp::lighting::light::const_object_ref_vector const &_lights
)
{
	sge::opengl::state::set_array<
		sge::opengl::state::ffp::lighting::light::object
	>(
		sge::opengl::context::use<
			sge::opengl::state::ffp::lighting::light::context
		>(
			fcppt::make_ref(
				_context
			)
		),
		_lights,
		sge::opengl::state::convert::light_index
	);
}
