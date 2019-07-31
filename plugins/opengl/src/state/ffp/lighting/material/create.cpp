//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/state/ffp/lighting/material/create.hpp>
#include <sge/opengl/state/ffp/lighting/material/make_actors.hpp>
#include <sge/opengl/state/ffp/lighting/material/object.hpp>
#include <sge/renderer/state/ffp/lighting/material/object.hpp>
#include <sge/renderer/state/ffp/lighting/material/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::state::ffp::lighting::material::object_unique_ptr
sge::opengl::state::ffp::lighting::material::create(
	sge::renderer::state::ffp::lighting::material::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::state::ffp::lighting::material::object
		>(
			fcppt::make_unique_ptr<
				sge::opengl::state::ffp::lighting::material::object
			>(
				sge::opengl::state::ffp::lighting::material::make_actors(
					_parameters
				)
			)
		);
}
