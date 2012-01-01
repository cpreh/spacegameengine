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


#ifndef SGE_RENDERER_DEPTH_STENCIL_BUFFER_HPP_INCLUDED
#define SGE_RENDERER_DEPTH_STENCIL_BUFFER_HPP_INCLUDED

namespace sge
{
namespace renderer
{

/**
 * \brief The namespace for the depth stencil buffer enum
*/
namespace depth_stencil_buffer
{
/**
 * The enum type for depth stencil buffer types
*/
enum type
{
	/**
	 * \brief No depth buffer and no stencil buffer
	*/
	off,
	/**
	 * \brief 16 bit depth buffer, no stencil buffer
	*/
	d16,
	/**
	 * \brief 24 bit depth buffer, no stencil buffer
	*/
	d24,
	/**
	 * \brief 32 bit depth buffer, no stencil buffer
	*/
	d32,
	/**
	 * \brief 24 bit depth buffer, 8 bit stencil buffer
	*/
	d24s8
};
}

}
}

#endif
