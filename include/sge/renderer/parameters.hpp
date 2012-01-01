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


#ifndef SGE_RENDERER_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/multi_sample_type.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/screen_mode.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/vsync.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief General parameters for a renderer::device
 *
 * Used to create a renderer::device or a renderable window. The settings
 * described by this class are immutable and (currently) cannot be changed
 * after a device has been created. Settings include resolution, bit depth,
 * depth buffer, stencil buffer, vsync and multi sampling.
 *
 * \see renderer::system::create_device
 * \see renderer::system::create_window
*/
class parameters
{
public:
	/**
	 * \brief Constructs renderer parameters
	 *
	 * \param screen_mode The screen mode to use
	 *
	 * \param depth_stencil The depth stencil setting
	 *
	 * \param vsync Switches vsync on or off
	 *
	 * \param multi_samples Specifies how many samples should be rendered,
	 * which must be >=1, or renderer::no_multi_sampling
	*/
	SGE_RENDERER_SYMBOL
	parameters(
		renderer::screen_mode const &screen_mode,
		renderer::depth_stencil_buffer::type depth_stencil,
		renderer::vsync::type vsync,
		renderer::multi_sample_type multi_samples
	);

	/**
	 * \brief Returns the screen mode
	*/
	SGE_RENDERER_SYMBOL
	renderer::screen_mode const &
	screen_mode() const;

	/**
	 * \brief Returns the depth stencil buffer settings
	*/
	SGE_RENDERER_SYMBOL
	renderer::depth_stencil_buffer::type
	depth_stencil_buffer() const;

	/**
	 * \brief Returns whether vsync should be used
	*/
	SGE_RENDERER_SYMBOL
	renderer::vsync::type
	vsync() const;

	/**
	 * \brief Returns the number of multi samples
	*/
	SGE_RENDERER_SYMBOL
	renderer::multi_sample_type const
	samples() const;
private:
	renderer::screen_mode screen_mode_;

	renderer::depth_stencil_buffer::type depth_stencil_buffer_;

	renderer::vsync::type vsync_;

	renderer::multi_sample_type samples_;
};

}
}

#endif
