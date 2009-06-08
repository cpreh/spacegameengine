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


#include "../texture_functions.hpp"
#include "../check_state.hpp"
#include "../convert_texture_filter.hpp"
#include "../glew.hpp"
#include "../pbo.hpp" // TODO: maybe put this somewhere else
#include <sge/log/headers.hpp>
#include <sge/math/rect/basic_impl.hpp>
#include <sge/math/rect/output.hpp>
#include <sge/math/is_power_of_2.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/renderer/filter/texture.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture_creation_failed.hpp>
#include <sge/log/logger.hpp>
#include <sge/log/global.hpp>
#include <sge/log/temporary_output.hpp>
#include <sge/text.hpp>
#include <sge/format.hpp>
#include <ostream>

namespace
{

bool need_mipmap(
	sge::renderer::filter::min::type);

bool have_anisotropic_filter();

}

GLuint sge::ogl::gen_texture()
{
	GLuint id;
	glGenTextures(1, &id);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glGenTextures failed"),
		sge::renderer::exception
	)
	
	return id;
}

void sge::ogl::delete_texture(
	GLuint const id)
{
	glDeleteTextures(1, &id);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glDeleteTextures failed"),
		sge::renderer::exception
	)
}

void sge::ogl::set_texture(
	GLenum const tex_type,
	GLenum const format,
	GLenum const type,
	renderer::filter::texture const &filter,
	renderer::dim_type const &dim,
	renderer::const_raw_pointer const src)
{
	if(dim.w() < 64 || dim.h() < 64)
		SGE_LOG_WARNING(
			log::global(),
			log::_1
				<< SGE_TEXT("opengl implementations are not required to support textures smaller than 64x64.")\
				SGE_TEXT(" Specified texture size was ")
				<< dim
				<< SGE_TEXT('.')
		);

	if(!math::is_power_of_2(dim.w()) || !math::is_power_of_2(dim.h()))
		SGE_LOG_WARNING(
			log::global(),
			log::_1
				<< SGE_TEXT("opengl implementations are not required to support textures with dimensions that are not a power of 2.")\
				SGE_TEXT(" Specified texture size was ")
				<< dim
				<< SGE_TEXT('.')
		);
		
	glTexImage2D(
		tex_type,
		0,
		4,
		static_cast<GLsizei>(dim.w()),
		static_cast<GLsizei>(dim.h()),
		0,
		format,
		type,
		src
	);

	SGE_OPENGL_CHECK_STATE(
		sge::str(
			sge::format(
				SGE_TEXT("Creation of texture with size %1% failed!"))
			% dim
		),
		sge::renderer::texture_creation_failed
	);

	if(need_mipmap(filter.min()))
		build_mipmaps(
			tex_type,
			format,
			type,
			dim,
			src
		);
}

void sge::ogl::build_mipmaps(
	GLenum const tex_type,
	GLenum const format,
	GLenum const type,
	renderer::dim_type const &dim,
	renderer::const_raw_pointer const src)
{
	if(!src)
		throw exception(
			SGE_TEXT("ogl::build_mipmaps: src is 0!"));

	gluBuild2DMipmaps(
		tex_type,
		format,
		static_cast<GLsizei>(dim.w()),
		static_cast<GLsizei>(dim.h()),
		format,
		type,
		src
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("gluBuild2DMipmaps failed"),
		sge::renderer::texture_creation_failed
	)
}

void sge::ogl::set_texture_rect(
	GLenum const tex_type,
	GLenum const format,
	GLenum const type,
	renderer::filter::texture const &filter,
	renderer::dim_type const &dim,
	renderer::lock_rect const &r,
	renderer::const_raw_pointer const src)
{
	if(!src && !pbo_in_hardware())
		throw exception(
			SGE_TEXT("ogl::set_texture_rect(): src is 0!"));

	if(r.right() > dim.w() || r.bottom() > dim.h())
		throw exception(
			(sge::format(
				SGE_TEXT("rect for setting a texture is out of range (rect=%1%, dim=%2%)!"))
				% r
				% dim).str());

	if(need_mipmap(filter.min()))
		throw exception(
			SGE_TEXT("You can't specify an update rect while using mipmaps."));

	glTexSubImage2D(
		tex_type,
		0,
		static_cast<GLint>(r.left()),
		static_cast<GLint>(r.top()),
		static_cast<GLsizei>(r.w()),
		static_cast<GLsizei>(r.h()),
		format,
		type,
		src
	);

	SGE_OPENGL_CHECK_STATE(
		sge::str(
			sge::format(
				SGE_TEXT("glTexSubImage2D with rect %1% failed")
			)
			% r
		),
		sge::renderer::exception
	)
}

void sge::ogl::get_tex_image(
	GLenum const format,
	GLenum const type,
	renderer::raw_pointer const dest)
{
	glGetTexImage(
		GL_TEXTURE_2D,
		0,
		format,
		type,
		dest
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glGetTexImage failed"),
		sge::renderer::exception
	)
}

void sge::ogl::tex_parameter_i(
	GLenum const type,
	GLenum const name,
	GLint const value)
{
	glTexParameteri(type, name, value);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glTexParameteri failed"),
		sge::renderer::exception
	)
	
}

void sge::ogl::bind_texture(
	GLenum const type,
	GLuint const value)
{
	glBindTexture(type, value);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glBindTexture failed"),
		sge::renderer::exception
	)
}

void sge::ogl::set_texture_filter(
	GLenum const type,
	renderer::filter::texture const &filter)
{
	tex_parameter_i(
		type,
		GL_TEXTURE_MIN_FILTER,
		convert_texture_filter(filter.min())
	);
	
	tex_parameter_i(
		type,
		GL_TEXTURE_MAG_FILTER,
		convert_texture_filter(filter.mag())
	);

	if(!filter.anisotropy())
		return;
	
	if(!have_anisotropic_filter())
	{
		SGE_LOG_WARNING(
			log::global(),
			log::_1
				<< SGE_TEXT("anisotropic filtering is not supported!")
		);
		return;
	}
	
	try
	{
		tex_parameter_i(
			type,
			GL_TEXTURE_MAX_ANISOTROPY_EXT,
			filter.anisotropy()
		);
	}
	catch(exception const &)
	{
		SGE_LOG_WARNING(
			log::global(),
			log::_1
				<< SGE_TEXT("anisotropy level ")
				<< filter.anisotropy()
				<< SGE_TEXT(" not supported!")
		);
	}
}

namespace
{

bool need_mipmap(
	sge::renderer::filter::min::type const filter)
{
	switch(filter) {
	case sge::renderer::filter::min::mipmap:
	case sge::renderer::filter::min::trilinear:
		return true;
	default:
		return false;
	}
}

bool have_anisotropic_filter()
{
	static bool const b(
		sge::ogl::glew_is_supported(
			"GL_EXT_texture_filter_anisotropic"
		)
	);

	return b;
}

}
