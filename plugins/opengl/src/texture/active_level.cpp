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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/funcs/set_active_level.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/log/object_fwd.hpp>


sge::opengl::texture::active_level::active_level(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context,
	sge::renderer::texture::stage const _stage
)
:
	stage_(
		_stage
	)
{
	sge::opengl::texture::funcs::set_active_level(
		_log,
		_context,
		_stage
	);
}

sge::opengl::texture::active_level::~active_level()
{
}

sge::renderer::texture::stage
sge::opengl::texture::active_level::stage() const
{
	return
		stage_;
}
