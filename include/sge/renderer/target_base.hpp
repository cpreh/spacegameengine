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


#ifndef SGE_RENDERER_TARGET_BASE_HPP_INCLUDED
#define SGE_RENDERER_TARGET_BASE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/scissor_area.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/target_base_fwd.hpp>
#include <sge/renderer/viewport.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace renderer
{

/**
 * \brief The base class for render targets
 *
 * This class is the base class of renderer::target, which is an off screen
 * target, and renderer::onscreen_target. It can be used to set and retrieve
 * both the associated viewport and scissor area.
 *
 * The viewport describes a rectangular portion of the target which
 * will be rendered to. Initially, this covers the whole buffer.
 *
 * The scissor area describes a rectangular portion of the target which will be
 * updated when rendering. Initially, the scissor area is unspecified. Scissor
 * tests will only be performed if renderer::state::bool_::enable_scissor_test
 * is true.
*/
class SGE_CLASS_SYMBOL target_base
{
	FCPPT_NONCOPYABLE(
		target_base
	);
protected:
	SGE_RENDERER_SYMBOL
	target_base();
public:
	/**
	 * \brief Sets the viewport
	 *
	 * Sets the viewport of the target to \a viewport
	 *
	 * \param viewport The viewport to set
	*/
	virtual void
	viewport(
		renderer::viewport const &viewport
	) = 0;

	/**
	 * \brief Returns the current viewport
	*/
	virtual
	renderer::viewport const
	viewport() const = 0;

	/**
	 * \brief Sets the scissor area
	 *
	 * Sets the scissor area of the target to \a area
	 *
	 * \param area The scissor area to set
	*/
	virtual void
	scissor_area(
		renderer::scissor_area const &area
	) = 0;

	/**
	 * \brief Returns the current scissor area
	*/
	virtual renderer::scissor_area const
	scissor_area() const = 0;

	SGE_RENDERER_SYMBOL
	virtual ~target_base() = 0;
};

}
}

#endif
