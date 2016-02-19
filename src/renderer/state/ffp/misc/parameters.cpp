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
