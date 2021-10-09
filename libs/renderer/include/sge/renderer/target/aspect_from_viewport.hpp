//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TARGET_ASPECT_FROM_VIEWPORT_HPP_INCLUDED
#define SGE_RENDERER_TARGET_ASPECT_FROM_VIEWPORT_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <fcppt/optional/object_impl.hpp>

namespace sge::renderer::target
{

/**
\brief Calculates the aspect from a viewport

Calculates the aspect from \a viewport as it would be calculated by
sge::renderer::aspect.

\see sge::renderer::aspect
*/
SGE_RENDERER_DETAIL_SYMBOL
fcppt::optional::object<sge::renderer::scalar>
aspect_from_viewport(sge::renderer::target::viewport const &viewport);

}

#endif
