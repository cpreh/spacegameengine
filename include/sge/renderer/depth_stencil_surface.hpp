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


#ifndef SGE_RENDERER_DEPTH_STENCIL_SURFACE_HPP_INCLUDED
#define SGE_RENDERER_DEPTH_STENCIL_SURFACE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_surface_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief Describes an abstraction of a depth stencil store
 *
 * A depth stencil surface describes an abstraction of a depth stencil store.
 * For example, the every mipmap level of a renderer::texture::depth_stencil is
 * a depth stencil surface. A renderer::target (including the
 * renderer::onscreen_target) can have a depth stencil surface as well.
*/
class SGE_CLASS_SYMBOL depth_stencil_surface
{
	FCPPT_NONCOPYABLE(
		depth_stencil_surface
	);
protected:
	SGE_RENDERER_SYMBOL
	depth_stencil_surface();
public:
	/**
	 * \brief The dimension type
	 *
	 * Specifies a two dimensional size in pixels
	*/
	typedef renderer::dim2 dim;

	SGE_RENDERER_SYMBOL
	virtual ~depth_stencil_surface() = 0;

	/**
	 * \brief The size of the buffer
	 *
	 * \return The size of the buffer as a two dimensional size of pixels
	*/
	virtual dim const
	size() const = 0;

	/**
	 * \brief The format of the surface
	 *
	 * \return The format of the surface
	*/
	virtual renderer::depth_stencil_format::type
	format() const = 0;

	// TODO!
};

}
}

#endif
