/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/context/device/base.hpp>
#include <sge/opengl/context/device/id.hpp>
#include <sge/opengl/context/device/make_id.hpp>
#include <sge/opengl/state/ffp/clip_plane/context.hpp>
#include <sge/renderer/state/index_count.hpp>


sge::opengl::state::ffp::clip_plane::context::context()
:
	sge::opengl::context::device::base(),
	indices_(
		0u
	)
{
}

sge::opengl::state::ffp::clip_plane::context::~context()
{
}

sge::renderer::state::index_count
sge::opengl::state::ffp::clip_plane::context::indices() const
{
	return indices_;
}

void
sge::opengl::state::ffp::clip_plane::context::indices(
	sge::renderer::state::index_count const _indices
)
{
	indices_ = _indices;
}

sge::opengl::context::device::id const
sge::opengl::state::ffp::clip_plane::context::static_id(
	sge::opengl::context::device::make_id()
);
