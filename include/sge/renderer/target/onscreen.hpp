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


#ifndef SGE_RENDERER_TARGET_ONSCREEN_HPP_INCLUDED
#define SGE_RENDERER_TARGET_ONSCREEN_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/color_surface_fwd.hpp>
#include <sge/renderer/symbol.hpp>
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
 * \brief The target used to render on screen
 *
 * Every renderer::device will have an onscreen target by default. It is used
 * to render anything on screen (instead of rendering to, for example, a
 * texture).
 *
 * \see renderer::target_base
 * \see renderer::device::onscreen_target
*/
class SGE_CLASS_SYMBOL onscreen
:
	public sge::renderer::target::base
{
	FCPPT_NONCOPYABLE(
		onscreen
	);
protected:
	SGE_RENDERER_SYMBOL
	onscreen();
public:
	/**
	 * \brief Returns the associated color surface
	*/
	virtual
	sge::renderer::color_surface const &
	surface() const = 0;

	SGE_RENDERER_SYMBOL
	virtual
	~onscreen() = 0;
};

}
}
}

#endif
