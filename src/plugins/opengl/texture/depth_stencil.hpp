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


#ifndef SGE_OPENGL_TEXTURE_DEPTH_STENCIL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_DEPTH_STENCIL_HPP_INCLUDED

#include "depth_stencil_fwd.hpp"
#include "base.hpp"
#include "../context/object_fwd.hpp"
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface_ptr.hpp>
#include <sge/renderer/texture/depth_stencil.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <fcppt/math/dim/basic_decl.hpp>

namespace sge
{
namespace opengl
{
namespace texture
{

class depth_stencil
:
	public sge::renderer::texture::depth_stencil,
	public opengl::texture::base
{
	FCPPT_NONCOPYABLE(
		depth_stencil
	);
public:
	explicit depth_stencil(
		opengl::context::object &,
		dim const &,
		renderer::depth_stencil_format::type
	);

	~depth_stencil();

	dim const
	size() const;

	renderer::depth_stencil_surface_ptr const
	surface() const;

	renderer::resource_flags_field const
	resource_flags() const;

	renderer::texture::capabilities_field const
	capabilities() const;
private:
	renderer::texture::mipmap::object const
	mipmap() const;

	opengl::context::object &context_;

	dim const size_;

	renderer::depth_stencil_format::type const format_;
};

}
}
}

#endif
