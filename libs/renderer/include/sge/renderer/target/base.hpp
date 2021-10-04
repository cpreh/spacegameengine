//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TARGET_BASE_HPP_INCLUDED
#define SGE_RENDERER_TARGET_BASE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/clear/parameters_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/scissor_area_fwd.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::renderer::target
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
class SGE_CORE_DETAIL_CLASS_SYMBOL base
{
	FCPPT_NONMOVABLE(
		base
	);
protected:
	SGE_RENDERER_DETAIL_SYMBOL
	base();
public:
	/**
	 * \brief Sets the viewport
	 *
	 * Sets the viewport of the target to \a viewport
	 *
	 * \param viewport The viewport to set
	*/
	virtual
	void
	viewport(
		sge::renderer::target::viewport const &viewport
	) = 0;

	/**
	 * \brief Returns the current viewport
	*/
	[[nodiscard]]
	virtual
	sge::renderer::target::viewport
	viewport() const = 0;

	/**
	 * \brief Sets the scissor area
	 *
	 * Sets the scissor area of the target to \a area
	 *
	 * \param area The scissor area to set
	*/
	virtual
	void
	scissor_area(
		sge::renderer::target::scissor_area const &area
	) = 0;

	/**
	 * \brief Returns the current scissor area
	*/
	[[nodiscard]]
	virtual
	sge::renderer::target::scissor_area
	scissor_area() const = 0;

	virtual
	void
	clear(
		sge::renderer::clear::parameters const &
	) = 0;

	SGE_RENDERER_DETAIL_SYMBOL
	virtual
	~base();
};

}

#endif
