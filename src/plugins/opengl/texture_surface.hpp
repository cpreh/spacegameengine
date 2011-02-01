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


#ifndef SGE_OPENGL_TEXTURE_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_SURFACE_HPP_INCLUDED

#include "texture_surface_fwd.hpp"
#include "common.hpp"
#include "texture_surface_base.hpp"
#include <sge/renderer/color_surface.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class texture_surface
:
	public sge::renderer::color_surface,
	public opengl::texture_surface_base
{
	FCPPT_NONCOPYABLE(
		texture_surface
	)
public:
	texture_surface(
		GLenum type,
		GLuint id,
		renderer::stage_type
	);
	
	~texture_surface();
private:
	image2d::view::const_object const
	lock(
		rect_type const &
	) const;

	void
	unlock() const;

	dim_type const
	dim() const;

	dim_type const dim_;
};

}
}

#endif
