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


#ifndef SGE_RENDERER_ACTIVE_TARGET_HPP_INCLUDED
#define SGE_RENDERER_ACTIVE_TARGET_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/target_base_fwd.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief Returns the active target of a device
 *
 * \param device The device to return the target for
 *
 * \return If \c device.target() is renderer::optional_target() then \c
 * device.onscreen_target() is returned. Otherwise, \c *device.target() is
 * returned.
*/
SGE_RENDERER_SYMBOL
renderer::target_base &
active_target(
	renderer::device &device
);

}
}

#endif
