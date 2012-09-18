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


#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/state/core/rasterizer/context.hpp>
#include <sge/opengl/state/core/rasterizer/make_actors.hpp>
#include <sge/opengl/state/core/rasterizer/object.hpp>
#include <sge/renderer/state/core/rasterizer/default.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::opengl::state::core::rasterizer::context::context()
:
	sge::opengl::context::system::base(),
	default_state_(
		fcppt::make_unique_ptr<
			sge::opengl::state::core::rasterizer::object
		>(
			sge::opengl::state::core::rasterizer::make_actors(
				sge::renderer::state::core::rasterizer::default_()
			)
		)
	)
{
}

sge::opengl::state::core::rasterizer::context::~context()
{
}

sge::opengl::state::core::rasterizer::object const &
sge::opengl::state::core::rasterizer::context::default_state() const
{
	return
		*default_state_;
}

sge::opengl::context::system::id const
sge::opengl::state::core::rasterizer::context::static_id(
	sge::opengl::context::system::make_id()
);
