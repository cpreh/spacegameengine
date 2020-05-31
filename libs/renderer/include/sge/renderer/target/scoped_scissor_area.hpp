//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TARGET_SCOPED_SCISSOR_AREA_HPP_INCLUDED
#define SGE_RENDERER_TARGET_SCOPED_SCISSOR_AREA_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/target/base_ref.hpp>
#include <sge/renderer/target/scissor_area.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace renderer
{
namespace target
{

/**
 * \brief A scoped scissor block
 *
 * This class sets a new scissor area for a target in the constructor, saving
 * the old scissor area. In the destructor the old scissor area is restored.
*/
class scoped_scissor_area
{
	FCPPT_NONMOVABLE(
		scoped_scissor_area
	);
public:
	/**
	 * \brief Sets a new scissor area
	 *
	 * Sets the scissor area of \a target to \a area. It also saves the
	 * old scissor area of \a target which will be restored in the
	 * destructor.
	 *
	 * \param target The target to set the scissor area for
	 *
	 * \param area The new scissor area
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	scoped_scissor_area(
		sge::renderer::target::base_ref target,
		sge::renderer::target::scissor_area const &area
	);

	/**
	 * \brief Resets to the old scissor area
	*/
	SGE_RENDERER_DETAIL_SYMBOL
	~scoped_scissor_area();
private:
	sge::renderer::target::base_ref const target_;

	sge::renderer::target::scissor_area const old_area_;
};

}
}
}

#endif
