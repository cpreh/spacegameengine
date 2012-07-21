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


#ifndef SGE_RENDERER_DISPLAY_MODE_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_OBJECT_HPP_INCLUDED

#include <sge/renderer/symbol.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>


namespace sge
{
namespace renderer
{
namespace display_mode
{

/**
\brief Describes a display mode's pixel count, dimensions and refresh rate

This class is used to change the display mode of a monitor. Note, that the bit
depth of the display mode is not part of this structure because it is chosen by
the pixel format.
*/
class object
{
public:
	/**
	\brief Constructs a display mode

	\param pixel_size The size of the display mode in pixels

	\param dimensions The dimensions of the occupied space in millimeters

	\param refresh_rate The optional refresh rate in Hz. If this is empty,
	it means the default refresh rate.
	*/
	SGE_RENDERER_SYMBOL
	object(
		sge::renderer::display_mode::pixel_size const &pixel_size,
		sge::renderer::display_mode::optional_dimensions const &dimensions,
		sge::renderer::display_mode::optional_refresh_rate refresh_rate
	);

	/**
	\brief Returns the pixel size
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::display_mode::pixel_size const &
	pixel_size() const;

	/**
	\brief Returns the dimensions
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::display_mode::optional_dimensions const &
	dimensions() const;

	/**
	\brief Returns the refresh rate
	*/
	SGE_RENDERER_SYMBOL
	sge::renderer::display_mode::optional_refresh_rate const
	refresh_rate() const;
private:
	sge::renderer::display_mode::pixel_size pixel_size_;

	sge::renderer::display_mode::optional_dimensions dimensions_;

	sge::renderer::display_mode::optional_refresh_rate refresh_rate_;
};

}
}
}

#endif
