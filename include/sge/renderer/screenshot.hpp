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


#ifndef SGE_RENDERER_SCREENSHOT_HPP_INCLUDED
#define SGE_RENDERER_SCREENSHOT_HPP_INCLUDED

#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/filesystem/path.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief Takes a screenshot and saves it to disk
 *
 * Takes a screenshot of the color surface of the onscreen target
 * denoted by \a device. It will be saved to \a path by \a system.
 *
 * \note Make sure that \a system is able to save the file format specified by
 * \a path.
 *
 * \param device The device to take the screenshot from
 *
 * \param system The image system to use for saving
 *
 * \param path The path to save the screenshot to
*/
SGE_RENDERER_SYMBOL
void
screenshot(
	renderer::device const &device,
	image2d::system &system,
	fcppt::filesystem::path const &path
);

}
}

#endif
