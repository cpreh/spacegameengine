//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/misc/enable_point_sprites.hpp>
#include <sge/renderer/state/ffp/misc/local_viewer.hpp>
#include <sge/renderer/state/ffp/misc/normalize_normals.hpp>
#include <sge/renderer/state/ffp/misc/parameters.hpp>


sge::renderer::state::ffp::misc::parameters::parameters(
	sge::renderer::state::ffp::misc::enable_point_sprites const _enable_point_sprites,
	sge::renderer::state::ffp::misc::local_viewer const _local_viewer,
	sge::renderer::state::ffp::misc::normalize_normals const _normalize_normals
)
:
	enable_point_sprites_(
		_enable_point_sprites
	),
	local_viewer_(
		_local_viewer
	),
	normalize_normals_(
		_normalize_normals
	)
{
}

sge::renderer::state::ffp::misc::enable_point_sprites
sge::renderer::state::ffp::misc::parameters::enable_point_sprites() const
{
	return
		enable_point_sprites_;
}

sge::renderer::state::ffp::misc::local_viewer
sge::renderer::state::ffp::misc::parameters::local_viewer() const
{
	return
		local_viewer_;
}

sge::renderer::state::ffp::misc::normalize_normals
sge::renderer::state::ffp::misc::parameters::normalize_normals() const
{
	return
		normalize_normals_;
}
