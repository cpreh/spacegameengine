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


#ifndef SGE_RENDERER_CLEAR_FLAGS_HPP_INCLUDED
#define SGE_RENDERER_CLEAR_FLAGS_HPP_INCLUDED

namespace sge
{
namespace renderer
{

/**
 * \brief The namespace for the clear_flags enum
*/
namespace clear_flags
{
/**
 * \brief The enum type for clear flags
*/
enum type
{
	/**
	 * \brief Clear the back buffer
	 *
	 * The back buffer will be cleared with the value set via
	 * sge::renderer::state::color::back_buffer_clear_color
	*/
	back_buffer,
	/**
	 * \brief Clear the depth buffer
	 *
	 * The depth buffer will be cleared with the value set via
	 * sge::renderer::state::float_::depth_buffer_clear_val
	 *
	 * \warning The behaviour is undefined if the depth buffer is absent
	*/
	depth_buffer,
	/**
	 * \brief Clear the stencil buffer
	 *
	 * The stencil buffer will be cleared with the value set via
	 * sge::renderer::state::int_::stencil_buffer_clear_val.
	 *
	 * \warning The behaviour is undefined if the stencil buffer is absent
	*/
	stencil_buffer,
	size
};
}

}
}

#endif
