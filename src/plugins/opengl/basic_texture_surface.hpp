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


#ifndef SGE_OPENGL_BASIC_TEXTURE_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_BASIC_TEXTURE_SURFACE_HPP_INCLUDED

#include "common.hpp"
#include "texture_surface_base.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

template<
	typename Base
>
class basic_texture_surface
:
	public Base,
	public opengl::texture_surface_base
{
	FCPPT_NONCOPYABLE(
		basic_texture_surface
	)
public:
	typedef typename Base::dim_type dim_type;

	basic_texture_surface(
		GLenum texture_type,
		GLuint id,
		renderer::stage_type
	);
	
	~basic_texture_surface();
private:
	// TODO:!
	dim_type const
	dim() const;

	dim_type const dim_;
};

}
}

#endif
