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


#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/binding.hpp>
#include <sge/opengl/texture/render_binding.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/texture/stage.hpp>


sge::opengl::texture::render_binding::render_binding(
	sge::opengl::texture::active_level const &_active_level,
	sge::opengl::texture::type const _type
)
:
	sge::opengl::texture::binding(),
	stage_(
		_active_level.stage()
	),
	type_(
		_type
	)
{
}

sge::opengl::texture::render_binding::~render_binding()
{
}

sge::renderer::texture::stage const
sge::opengl::texture::render_binding::stage() const
{
	return stage_;
}

sge::opengl::texture::type const
sge::opengl::texture::render_binding::type() const
{
	return type_;
}
