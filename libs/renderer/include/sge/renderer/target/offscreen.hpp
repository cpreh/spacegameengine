//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TARGET_OFFSCREEN_HPP_INCLUDED
#define SGE_RENDERER_TARGET_OFFSCREEN_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/color_buffer/optional_surface_ref_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer/optional_surface_ref_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/offscreen_fwd.hpp>
#include <sge/renderer/target/surface_index.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace target
{

/**
\brief A target used to render off screen

This class represents a target that can render off screen. At least, it has to
be supplied with a color surface for index zero before it can be used for
rendering. Such a color surface is usually obtained from a texture level. A
texture whose texture level should be used as a color surface in an offscreen
target must be created with
sge::renderer::texture::capabilities::render_target. A color surface at level
one or higher cannot be used with the fixed function pipeline. A depth stencil
surface can also be supplied so that offscreen rendering can use a depth or a
stencil buffer, respectively. Such a depth stencil surface can either be
created by sge::renderer::device::create_depth_stencil_surface or obtained from
a depth stencil texture. Initially, the target has no color surfaces and no
depth stencil surface.

\see sge::renderer::device::create_target
\see sge::renderer::device::create_depth_stencil_surface
\see sge::renderer::device::create_depth_stencil_texture
\see sge::renderer::texture::planar::level
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL offscreen
:
	public sge::renderer::target::base
{
	FCPPT_NONCOPYABLE(
		offscreen
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	offscreen();
public:
	/**
	\brief Sets or unsets a color surface for a surface level

	Sets \a surface to \a level or unsets the surface for \a level if \a
	surface is empty. Initially, no color surface is set.

	\param surface The color surface to set or an empty optional to unset
	the surface

	\param level The level to set the surface for. Level 0 is the one that
	will be used by the fixed function pipeline.
	*/
	virtual
	void
	color_surface(
		sge::renderer::color_buffer::optional_surface_ref const &surface,
		sge::renderer::target::surface_index level
	) = 0;

	/**
	\brief Sets or unsets the depth stencil surface

	Sets \a surface to be used as the depth stencil surface or unsets the
	depth stencil surface if \a surface is empty. Initially, no depth
	stencil surface is set.

	\param surface The depth stencil surface to set or an empty optional to
	unset the surface
	*/
	virtual
	void
	depth_stencil_surface(
		sge::renderer::depth_stencil_buffer::optional_surface_ref const &surface
	) = 0;

	SGE_RENDERER_DETAIL_SYMBOL
	~offscreen()
	override;
};

}
}
}

#endif
