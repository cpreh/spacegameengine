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


#ifndef SGE_OPENGL_TEXTURE_VOLUME_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_VOLUME_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/volume_config_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class volume_config
{
	FCPPT_NONASSIGNABLE(
		volume_config
	);
public:
	typedef
	sge::opengl::fun_ref<
		PFNGLTEXIMAGE3DPROC
	>
	gl_tex_image_3d;

	typedef
	sge::opengl::fun_ref<
		PFNGLTEXSUBIMAGE3DPROC
	>
	gl_tex_sub_image_3d;

	volume_config(
		sge::opengl::texture::type,
		gl_tex_image_3d,
		gl_tex_sub_image_3d,
		GLenum max_extent_flag
	);

	sge::opengl::texture::type
	volume_texture_type() const;

	gl_tex_image_3d
	tex_image_3d() const;

	gl_tex_sub_image_3d
	tex_sub_image_3d() const;

	GLenum
	max_extent_flag() const;
private:
	sge::opengl::texture::type const volume_texture_type_;

	gl_tex_image_3d tex_image_3d_;

	gl_tex_sub_image_3d tex_sub_image_3d_;

	GLenum const max_extent_flag_;
};

}
}
}

#endif
