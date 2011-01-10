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


#ifndef SGE_OPENGL_VF_TEXPOS_ACTOR_HPP_INCLUDED
#define SGE_OPENGL_VF_TEXPOS_ACTOR_HPP_INCLUDED

#include "fp_actor.hpp"
#include "pointer.hpp"
#include "actor_parameters_fwd.hpp"
#include "../context/object_fwd.hpp"
#include "../multi_texture_context_fwd.hpp"
#include "../common.hpp"
#include <sge/renderer/vf/dynamic/texpos_fwd.hpp>
#include <sge/renderer/vf/vertex_size.hpp>

namespace sge
{
namespace opengl
{
namespace vf
{

class texpos_actor
:
	public fp_actor
{
public:
	explicit texpos_actor(
		actor_parameters const &,
		sge::renderer::vf::dynamic::texpos const &
	);
private:
	void
	on_use(
		vf::pointer
	) const;

	opengl::context::object &context_;
	
	GLint const elements_;

	GLenum const format_;

	renderer::vf::vertex_size const index_;
};

}
}
}

#endif
