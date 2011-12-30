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


#ifndef SGE_OPENGL_TEXTURE_DEPTH_STENCIL_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_DEPTH_STENCIL_SURFACE_HPP_INCLUDED

#include <sge/opengl/texture/basic_surface.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class depth_stencil_surface
:
	public opengl::texture::basic_surface<
		sge::renderer::depth_stencil_surface
	>
{
	FCPPT_NONCOPYABLE(
		depth_stencil_surface
	);
public:
	typedef opengl::texture::basic_surface<
		sge::renderer::depth_stencil_surface
	> base;

	depth_stencil_surface(
		texture::binding const &,
		texture::type,
		texture::id,
		renderer::depth_stencil_format::type
	);

	~depth_stencil_surface();
private:
	renderer::depth_stencil_format::type
	format() const;

	renderer::depth_stencil_format::type const format_;
};

}
}
}

#endif
