//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/misc/default.hpp>
#include <sge/renderer/state/ffp/misc/enable_point_sprites.hpp>
#include <sge/renderer/state/ffp/misc/local_viewer.hpp>
#include <sge/renderer/state/ffp/misc/normalize_normals.hpp>
#include <sge/renderer/state/ffp/misc/parameters.hpp>


sge::renderer::state::ffp::misc::parameters
sge::renderer::state::ffp::misc::default_()
{
	return
		sge::renderer::state::ffp::misc::parameters(
			sge::renderer::state::ffp::misc::enable_point_sprites(
				false
			),
			sge::renderer::state::ffp::misc::local_viewer(
				false
			),
			sge::renderer::state::ffp::misc::normalize_normals(
				false
			)
		);
}
