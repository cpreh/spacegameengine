/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/texture/base_fwd.hpp>
#include <sge/opengl/texture/bind_context.hpp>
#include <sge/opengl/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/container/index_map_impl.hpp>


sge::opengl::texture::bind_context::bind_context()
:
	sge::opengl::context::base(),
	map_()
{
}

sge::opengl::texture::bind_context::~bind_context()
{
}

sge::opengl::texture::const_optional_base_ref
sge::opengl::texture::bind_context::stage(
	sge::renderer::texture::stage const _stage
) const
{
	return
		map_[
			_stage.get()
		];
}

void
sge::opengl::texture::bind_context::stage(
	sge::renderer::texture::stage const _stage,
	sge::opengl::texture::const_optional_base_ref const &_texture
)
{
	map_[
		_stage.get()
	] =
		_texture;
}

sge::opengl::context::id const
sge::opengl::texture::bind_context::static_id(
	sge::opengl::context::make_id()
);
