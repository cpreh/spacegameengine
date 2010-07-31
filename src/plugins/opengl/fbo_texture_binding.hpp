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


#ifndef SGE_OPENGL_FBO_TEXTURE_BINDING_HPP_INCLUDED
#define SGE_OPENGL_FBO_TEXTURE_BINDING_HPP_INCLUDED

#include "fbo_fwd.hpp"
#include "fbo_context_fwd.hpp"
#include "texture_ptr.hpp"
#include <sge/renderer/texture_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

class fbo_texture_binding
{
	FCPPT_NONCOPYABLE(fbo_texture_binding)
public:
	explicit fbo_texture_binding(
		fbo_context const &,
		opengl::texture_ptr,
		fbo &
	);

	~fbo_texture_binding();

	sge::renderer::texture_ptr const
	texture() const;
private:
	sge::renderer::texture_ptr const texture_;
};

}
}

#endif
