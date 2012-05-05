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


#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/bind_context.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/optional_type.hpp>
#include <sge/opengl/texture/funcs/bind.hpp>
#include <sge/opengl/texture/funcs/set_active_level.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/container/index_map_impl.hpp>


sge::opengl::texture::bind_context::bind_context()
:
	render_textures_(),
	last_types_()
{
}

sge::opengl::texture::bind_context::~bind_context()
{
}

void
sge::opengl::texture::bind_context::bind_for_rendering(
	opengl::context::object &_context,
	opengl::texture::base const &_texture,
	renderer::texture::stage const _stage
)
{
	render_textures_[
		_stage.get()
	] = &_texture;

	texture::funcs::set_active_level(
		_context,
		_stage
	);

	texture::funcs::bind(
		_texture.type(),
		sge::opengl::texture::optional_id(
			_texture.id()
		)
	);

	texture::optional_type const last_type(
		last_types_[
			_stage.get()
		]
	);

	if(
		last_type
		==
		texture::optional_type(
			_texture.type()
		)
	)
		return;

	if(
		last_type
	)
		opengl::disable(
			last_type->get()
		);

	opengl::enable(
		_texture.type().get()
	);

	last_types_[
		_stage.get()
	] = _texture.type();
}

void
sge::opengl::texture::bind_context::unbind_for_rendering(
	opengl::context::object &_context,
	renderer::texture::stage const _stage
)
{
	texture::optional_type const last_type(
		last_types_[
			_stage.get()
		]
	);

	last_types_[
		_stage.get()
	].reset();

	if(
		!last_type
	)
		return;

	texture::funcs::set_active_level(
		_context,
		_stage
	);

	render_textures_[
		_stage.get()
	] = fcppt::null_ptr();

	texture::funcs::bind(
		*last_type,
		sge::opengl::texture::optional_id()
	);

	opengl::disable(
		last_type->get()
	);
}

sge::opengl::texture::base const *
sge::opengl::texture::bind_context::render_texture(
	renderer::texture::stage const _stage
)
{
	return
		render_textures_[
			_stage.get()
		];
}

sge::opengl::context::id const
sge::opengl::texture::bind_context::static_id(
	sge::opengl::context::make_id()
);
