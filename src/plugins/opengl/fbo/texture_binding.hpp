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


#ifndef SGE_OPENGL_FBO_TEXTURE_BINDING_HPP_INCLUDED
#define SGE_OPENGL_FBO_TEXTURE_BINDING_HPP_INCLUDED

#include "texture_binding_fwd.hpp"
#include "object_fwd.hpp"
#include "context_fwd.hpp"
#include "../texture_surface_base_ptr.hpp"
#include "../common.hpp"
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace fbo
{

class texture_binding
{
	FCPPT_NONCOPYABLE(
		texture_binding
	)
public:
	explicit texture_binding(
		fbo::context const &,
		opengl::texture_surface_base_ptr,
		fbo::object &,
		GLenum attachment
	);

	~texture_binding();

	opengl::texture_surface_base_ptr const
	surface() const;
private:
	opengl::texture_surface_base_ptr const surface_;
};

}
}
}

#endif
