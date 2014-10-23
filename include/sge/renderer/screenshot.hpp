/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{

/**
\brief Takes a screenshot and saves it to a path

\ingroup sge_renderer

Takes a screenshot of the color surface of the onscreen target denoted by \a
device. It will be saved to \a path by \a system.

\note Make sure that \a system is able to save the file format specified by \a
path.

\param device The device to take the screenshot from

\param system The image system to use for saving

\param path The path to save the screenshot to
*/
SGE_RENDERER_DETAIL_SYMBOL
void
screenshot(
	sge::renderer::device::core const &device,
	sge::image2d::system &system,
	boost::filesystem::path const &path
);

}
}

#endif
