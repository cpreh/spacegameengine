//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_TARGET_ASPECT_FROM_VIEWPORT_HPP_INCLUDED
#define SGE_RENDERER_TARGET_ASPECT_FROM_VIEWPORT_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace target
{

/**
 * \brief Calculates the aspect from a viewport
 *
 * Calculates the aspect from \a viewport as it would be calculated by
 * sge::renderer::aspect.
 *
 * \param viewport The viewport to calculate the aspect from
 *
 * \return The aspect
 *
 * \see sge::renderer::aspect
 *
 * \warning The behaviour is undefined if the viewport's width or height is
 * zero.
*/
SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::scalar
aspect_from_viewport(
	sge::renderer::target::viewport const &viewport
);

}
}
}

#endif
