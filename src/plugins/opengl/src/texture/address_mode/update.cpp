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


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/base_fwd.hpp>
#include <sge/opengl/texture/bind_context.hpp>
#include <sge/opengl/texture/render_binding.hpp>
#include <sge/opengl/texture/address_mode/context.hpp>
#include <sge/opengl/texture/address_mode/set.hpp>
#include <sge/opengl/texture/address_mode/update.hpp>
#include <sge/renderer/texture/address_mode_s.hpp>
#include <sge/renderer/texture/address_mode_t.hpp>
#include <sge/renderer/texture/address_mode_u.hpp>
#include <sge/renderer/texture/stage.hpp>


template<
	typename Mode
>
void
sge::opengl::texture::address_mode::update(
	sge::opengl::context::object &_context,
	Mode const _mode,
	sge::renderer::texture::stage const _stage
)
{
	if(
		!opengl::context::use<
			opengl::texture::address_mode::context
		>(
			_context
		).set(
			_stage,
			_mode
		)
	)
		return;

	opengl::texture::base const *const bound_texture(
		opengl::context::use<
			opengl::texture::bind_context
		>(
			_context
		).render_texture(
			_stage
		)
	);

	if(
		!bound_texture
	)
		return;

	opengl::texture::render_binding const already_bound(
		_context,
		_stage
	);

	opengl::texture::address_mode::set(
		_context,
		already_bound,
		*bound_texture,
		_stage
	);
}

#define SGE_OPENGL_TEXTURE_ADDRESS_MODE_INSTANTIATE_UPDATE(\
	mode_type\
)\
template \
void \
sge::opengl::texture::address_mode::update<\
	mode_type \
>( \
	sge::opengl::context::object &, \
	mode_type, \
	sge::renderer::texture::stage \
)

SGE_OPENGL_TEXTURE_ADDRESS_MODE_INSTANTIATE_UPDATE(
	sge::renderer::texture::address_mode_s
);

SGE_OPENGL_TEXTURE_ADDRESS_MODE_INSTANTIATE_UPDATE(
	sge::renderer::texture::address_mode_t
);

SGE_OPENGL_TEXTURE_ADDRESS_MODE_INSTANTIATE_UPDATE(
	sge::renderer::texture::address_mode_u
);
