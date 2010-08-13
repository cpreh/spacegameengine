/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../texture_context.hpp"
#include "../context/make_id.hpp"
#include "../glew/is_supported.hpp"

sge::opengl::texture_context::texture_context()
:
	anisotropic_filter_supported_(
		sge::opengl::glew::is_supported(
			"GL_EXT_texture_filter_anisotropic"
		)
	),
	generate_mipmap_flag_supported_(
		sge::opengl::glew::is_supported(
			"GL_VERSION_1_4"
		)
	),
	anisotropy_flag_(
		anisotropic_filter_supported_
		?
			GL_TEXTURE_MAX_ANISOTROPY_EXT
		:
			0
	),
	max_anisotropy_flag_(
		anisotropic_filter_supported_
		?
			GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
		:
			0
	),
	last_types_()
{}

sge::opengl::texture_context::~texture_context()
{
}

bool
sge::opengl::texture_context::anisotropic_filter_supported() const
{
	return anisotropic_filter_supported_;
}

bool
sge::opengl::texture_context::generate_mipmap_flag_supported() const
{
	return generate_mipmap_flag_supported_;
}

GLenum
sge::opengl::texture_context::anisotropy_flag() const
{
	return anisotropy_flag_;
}

GLenum
sge::opengl::texture_context::max_anisotropy_flag() const
{
	return max_anisotropy_flag_;
}

void
sge::opengl::texture_context::last_type(
	GLenum const _last_type,
	sge::renderer::stage_type const _stage
)
{
	if(
		last_types_.size() <= _stage
	)
		last_types_.resize(
			_stage + 1u
		);
	
	last_types_[
		_stage
	] = _last_type;
}

GLenum
sge::opengl::texture_context::last_type(
	sge::renderer::stage_type const _stage
) const
{
	return
		last_types_.size() <= _stage
		?
			invalid_type
		:
			last_types_[
				_stage
			];
}

GLenum const
sge::opengl::texture_context::invalid_type(0); // must be != GL_TEXTURE_2D/3D/...

sge::opengl::context::id const
sge::opengl::texture_context::static_id(
	sge::opengl::context::make_id()
);
