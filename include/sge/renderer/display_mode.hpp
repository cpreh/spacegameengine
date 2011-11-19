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


#ifndef SGE_RENDERER_DISPLAY_MODE_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_HPP_INCLUDED

#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/display_mode_fwd.hpp>
#include <sge/renderer/refresh_rate.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief Describes a display mode's size, bit depth and refresh rate
 *
 * This class is used to change the display mode of a monitor.
 *
 * \see renderer::screen_mode
*/
class display_mode
{
public:
	/**
	 * \brief Constructs a display mode
	 *
	 * \param screen_size The screen size of the display mode
	 *
	 * \param bit_depth The bit depth of the display mode
	 *
	 * \param refresh_rate The refresh rate in Hz, can be
	 * renderer::refresh_rate_dont_care
	*/
	SGE_RENDERER_SYMBOL
	display_mode(
		renderer::screen_size const &screen_size,
		renderer::bit_depth::type bit_depth,
		renderer::refresh_rate refresh_rate
	);

	/**
	 * \brief Returns the screen size
	*/
	SGE_RENDERER_SYMBOL
	renderer::screen_size const &
	size() const;

	/**
	 * \brief Returns the bit depth
	*/
	SGE_RENDERER_SYMBOL
	renderer::bit_depth::type
	bit_depth() const;

	/**
	 * \brief Returns the refresh rate
	*/
	SGE_RENDERER_SYMBOL
	renderer::refresh_rate const
	refresh_rate() const;
private:
	renderer::screen_size size_;

	renderer::bit_depth::type bit_depth_;

	renderer::refresh_rate refresh_rate_;
};

}
}

#endif
