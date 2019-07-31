//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TARGET_ONSCREEN_HPP_INCLUDED
#define SGE_RENDERER_TARGET_ONSCREEN_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/color_buffer/readable_surface_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{
namespace target
{

/**
\brief The target used to render on screen

Every device will have an onscreen target by default. It is used to render
anything on screen (instead of rendering to, for example, a texture).

\see sge::renderer::target_base
\see sge::renderer::device::onscreen_target
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL onscreen
:
	public sge::renderer::target::base
{
	FCPPT_NONCOPYABLE(
		onscreen
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	onscreen();
public:
	/**
	\brief Returns the associated color surface
	*/
	virtual
	sge::renderer::color_buffer::readable_surface const &
	surface() const = 0;

	SGE_RENDERER_DETAIL_SYMBOL
	~onscreen()
	override;
};

}
}
}

#endif
