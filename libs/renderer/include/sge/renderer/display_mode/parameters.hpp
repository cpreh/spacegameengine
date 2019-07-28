/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_DISPLAY_MODE_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/display_mode/optional_fullscreen.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <sge/renderer/display_mode/parameters_fwd.hpp>
#include <sge/renderer/display_mode/vsync.hpp>


namespace sge
{
namespace renderer
{
namespace display_mode
{

/**
\brief Parameters used to set a display mode.

\see sge::renderer::system::create_device
*/
class parameters
{
public:
	// TODO: Remove this
	SGE_RENDERER_DETAIL_SYMBOL
	parameters(
		sge::renderer::display_mode::vsync,
		sge::renderer::display_mode::optional_object const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	parameters(
		sge::renderer::display_mode::vsync,
		sge::renderer::display_mode::optional_fullscreen const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::display_mode::vsync
	vsync() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::display_mode::optional_fullscreen const &
	fullscreen() const;
private:
	sge::renderer::display_mode::vsync vsync_;

	sge::renderer::display_mode::optional_fullscreen fullscreen_;
};

}
}
}

#endif
