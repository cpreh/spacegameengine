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


#ifndef SGE_RENDERER_ADD_DEPTH_STENCIL_SURFACE_TO_TARGET_HPP_INCLUDED
#define SGE_RENDERER_ADD_DEPTH_STENCIL_SURFACE_TO_TARGET_HPP_INCLUDED

#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/target_fwd.hpp>

namespace sge
{
namespace renderer
{

/**
 * \brief Adds a depth stencil surface to a target
 *
 * Adds a depth stencil surface with format \a format to \a target, which will
 * have the same size as the target's color surface.
 *
 * \param device The device used to create the depth stencil surface
 * \param target The target to add the depth stencil surface to
 * \param format The format to use
 *
 * \throw sge::renderer::exception if \a target has no color surface
*/
SGE_RENDERER_SYMBOL
void
add_depth_stencil_surface_to_target(
	renderer::device &device,
	renderer::target &target,
	renderer::depth_stencil_format::type format
);

}
}

#endif

