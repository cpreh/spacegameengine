/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_FUNC_SEPARATE_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_FUNC_SEPARATE_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/func_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/read_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace depth_stencil
{
namespace stencil
{

sge::opengl::state::actor const
func_separate(
	GLenum side,
	sge::renderer::state::core::depth_stencil::stencil::func,
	sge::renderer::state::core::depth_stencil::stencil::ref,
	sge::renderer::state::core::depth_stencil::stencil::read_mask
);

}
}
}
}
}
}

#endif
