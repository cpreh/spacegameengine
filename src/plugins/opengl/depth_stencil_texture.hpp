/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_DEPTH_STENCIL_TEXTURE_HPP_INCLUDED
#define SGE_OPENGL_DEPTH_STENCIL_TEXTURE_HPP_INCLUDED

#include "depth_stencil_texture_fwd.hpp"
#include "texture_holder.hpp"
#include "texture_base.hpp"
#include "common.hpp"
#include "context/object_fwd.hpp"
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_texture.hpp>
#include <fcppt/math/dim/basic_decl.hpp>

namespace sge
{
namespace opengl
{

class depth_stencil_texture
:
	public sge::renderer::depth_stencil_texture,
	public opengl::texture_base
{
	FCPPT_NONCOPYABLE(depth_stencil_texture)
public:
	explicit depth_stencil_texture(
		opengl::context::object &,
		dim_type const &,
		renderer::depth_stencil_format::type
	);

	~depth_stencil_texture();

	GLuint
	id() const;

	void
	bind_me() const;

	dim_type const
	dim() const;

	renderer::resource_flags_field const
	flags() const;

	void
	debug(); // TODO: remove this!
private:
	texture_holder const holder_;

	dim_type const dim_;

	GLenum const
		format_,
		format_type_;
};

}
}

#endif
