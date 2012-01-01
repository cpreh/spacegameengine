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


#ifndef SGE_RENDERER_COLOR_SURFACE_HPP_INCLUDED
#define SGE_RENDERER_COLOR_SURFACE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/color_surface_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief Describes an abstraction of a color store
 *
 * A color surface describes an abstraction of a color store. For example,
 * every mipmap level of a renderer::texture::planar is a color surface. A
 * renderer::target (including the renderer::onscreen_target) also have a color
 * surface.
*/
class SGE_CLASS_SYMBOL color_surface
{
	FCPPT_NONCOPYABLE(
		color_surface
	);
protected:
	SGE_RENDERER_SYMBOL
	color_surface();
public:
	SGE_RENDERER_SYMBOL
	virtual ~color_surface() = 0;

	/**
	 * \brief The size type
	 *
	 * Specifies a size in pixels
	*/
	typedef renderer::size_type size_type;

	/**
	 * \brief The dimension type
	 *
	 * Specifies a two dimensional size in pixels
	*/
	typedef renderer::dim2 dim;

	/**
	 * \brief The rect type
	 *
	 * Specifies a rectangle in pixels
	*/
	typedef renderer::lock_rect rect;

	/**
	 * \brief The view type
	 *
	 * The view type of the lock
	*/
	typedef sge::image2d::view::const_object const_view;

	/**
	 * \brief Locks the whole buffer readonly
	 *
	 * Locks the whole buffer readonly
	 *
	 * \return The view of the locked region
	 *
	 * \warning The behaviour is undefined if the buffer is already locked
	*/
	SGE_RENDERER_SYMBOL
	const_view const
	lock() const;

	/**
	 * \brief Locks a portion of the buffer readonly
	 *
	 * Reads the portion of the buffer specified by \a area readonly.
	 *
	 * \return The view of the locked region
	 *
	 * \warning The behaviour is undefined if the buffer is already locked
	 * \warning The behaviour is undefined if \a area is out of range
	*/
	virtual const_view const
	lock(
		rect const &area
	) const = 0;

	/**
	 * \brief Unlocks the buffer
	 *
	 * Unlocks the currently locked buffer region.
	 *
	 * \warning The behaviour is undefined if the buffer is not locked
	*/
	virtual void
	unlock() const = 0;

	/**
	 * \brief The size of the buffer
	 *
	 * \return The size of the buffer as a two dimensional size of pixels
	*/
	virtual dim const
	size() const = 0;

	/**
	 * \brief A rectangle describing the size of the buffer
	 *
	 * Returns a rectangle describing the size of the buffer that has its
	 * position set to zero.
	 *
	 * \return \c rect(rect::null(), this->dim())
	*/
	SGE_RENDERER_SYMBOL
	rect const
	area() const;

	/**
	 * \brief The number of pixels stored in the buffer
	 *
	 * Returns the number of pixels stored in the buffer as a size_type
	 *
	 * \return \c this->dim().content()
	*/
	SGE_RENDERER_SYMBOL
	size_type
	content() const;
};

}
}

#endif
