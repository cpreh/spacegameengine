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


#ifndef SGE_RENDERER_TARGET_HPP_INCLUDED
#define SGE_RENDERER_TARGET_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/depth_stencil_surface_ptr.hpp>
#include <sge/renderer/optional_dim2.hpp>
#include <sge/renderer/surface_index.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/target_base.hpp>
#include <sge/renderer/target_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief A target used to render off screen
 *
 * This class represents a target that can render off screen. At least, it has
 * to be supplied with a color surface for index zero before it can be used for
 * rendering. Such a color surface is usually obtained from a texture level. A
 * texture whose texture level should be used as a color surface in an
 * offscreen target must be created with
 * renderer::texture::capabilities::render_target. A color surface at level one
 * or higher cannot be used with the fixed function pipeline. A depth stencil
 * surface can also be supplied so that offscreen rendering can use a depth or
 * a stencil buffer, respectively. Such a depth stencil surface can either be
 * created by renderer::device::create_depth_stencil_surface or obtained from a
 * depth stencil texture. Initially, the target has no color surfaces and no
 * depth stencil surface and no dimension. The first surface that is set will
 * dictate the dimension of the target, which every other surface must match.
 * If all surfaces are unset, the dimension will also be unset.
 *
 * \see renderer::add_depth_stencil_surface_to_target
 * \see renderer::device::create_target
 * \see renderer::device::create_depth_stencil_surface
 * \see renderer::device::create_depth_stencil_texture
 * \see renderer::texture::planar::surface
*/
class SGE_CLASS_SYMBOL target
:
	public sge::renderer::target_base
{
	FCPPT_NONCOPYABLE(
		target
	);
protected:
	SGE_RENDERER_SYMBOL
	target();
public:
	/**
	 * \brief Sets or unsets a color surface for a surface level
	 *
	 * Sets \a surface to \a level or unsets the surface for \a level if \a
	 * surface is \c renderer::color_surface_ptr().
	 * Initially, no color surface is set.
	 * If a surface is set, it also sets the dimension of the target to the
	 * dimension of \a surface if no surface has been previously set. The
	 * target will assume shared ownership of the surface. The dimension
	 * will be unset when the last surface is unset.
	 *
	 * \param surface The color surface to set or \c
	 * renderer::color_surface_ptr() to unset the surface
	 *
	 * \param level The level to set the surface for. Level 0 is the one
	 * that will be used by the fixed function pipeline.
	 *
	 * \throw renderer::exception if the dimension of \a surface doesn't
	 * match the current dimension.
	*/
	virtual void
	color_surface(
		renderer::color_surface_ptr surface,
		renderer::surface_index level
	) = 0;

	/**
	 * \brief Sets or unsets the depth stencil surface
	 *
	 * Sets \a surface to be used as the depth stencil surface or unsets
	 * the depth stencil surface if \a surface is \c
	 * renderer::depth_stencil_surface_ptr(). Initially, no depth stencil
	 * surface is set. If the surface is set, it also sets the dimension
	 * of the target to the dimension of \a surface if no surface has been
	 * previously set. The target will assume shared ownership of the
	 * surface. The dimension will be unset when the last surface is
	 * unset.
	 *
	 * \param surface The depth stencil surface to set or \c
	 * renderer::depth_stencil_surface_ptr() to unset the surface
	 *
	 * \throw renderer::exception if the dimension of \a surface doesn't
	 * match the current dimension.
	*/
	virtual void
	depth_stencil_surface(
		renderer::depth_stencil_surface_ptr surface
	) = 0;

	/**
	 * \brief Returns the current dimension or \c renderer::optional_dim2()
	 *
	 * The current dimension is the dimension of the first surface that is
	 * set. If all surfaces are unset, the dimension will also be unset.
	 *
	 * \return The current dimension or \c renderer::optional_dim2() if no
	 * surface has been set yet.
	*/
	virtual renderer::optional_dim2 const
	size() const = 0;

	SGE_RENDERER_SYMBOL
	virtual ~target() = 0;
};

}
}

#endif
