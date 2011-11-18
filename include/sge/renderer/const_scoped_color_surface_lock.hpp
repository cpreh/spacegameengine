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


#ifndef SGE_RENDERER_CONST_SCOPED_COLOR_SURFACE_LOCK_HPP_INCLUDED
#define SGE_RENDERER_CONST_SCOPED_COLOR_SURFACE_LOCK_HPP_INCLUDED

#include <sge/image2d/view/const_object.hpp>
#include <sge/renderer/color_surface_fwd.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/variant/object_impl.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief Locks a color surface readonly.
 *
 * Used for locking renderer::color_surface. It locks the color surface in the
 * constructor and unlocks it in the destructor.
*/

class const_scoped_color_surface_lock
{
	FCPPT_NONCOPYABLE(
		const_scoped_color_surface_lock
	);
public:
	/**
	 * \brief Locks an entire color surface
	 *
	 * \param surface The surface to lock
	 *
	 * \warning The behaviour is undefined if the color surface is already
	 * locked
	*/
	SGE_RENDERER_SYMBOL
	explicit const_scoped_color_surface_lock(
		renderer::color_surface const &surface
	);

	/**
	 * \brief Locks a portion of a color surface
	 *
	 * Locks the portion of \a surface described by \a area
	 *
	 * \param surface The color surface to lock
	 *
	 * \param area The area to lock
	 *
	 * \warning The behaviour is undefined if the color surface is already
	 * locked
	 * \warning The behaviour is undefined if \a area is out of range
	*/
	SGE_RENDERER_SYMBOL
	const_scoped_color_surface_lock(
		renderer::color_surface const &surface,
		renderer::lock_rect const &area
	);

	/**
	 * \brief Obtain the view of the locked region
	 *
	 * \return The view of the locked region
	*/
	SGE_RENDERER_SYMBOL
	image2d::view::const_object const
	value() const;

	/**
	 * \brief Unlocks the color surface
	 *
	 * \warning The behaviour is undefined if the color surface has been
	 * locked again or unlocked in between the constructor and destructor
	*/
	SGE_RENDERER_SYMBOL
	~const_scoped_color_surface_lock();
private:
	renderer::color_surface const &color_surface_;

	image2d::view::const_object const view_;
};

}
}

#endif
