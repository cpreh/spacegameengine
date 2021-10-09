//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TARGET_OPTIONAL_OFFSCREEN_REF_FWD_HPP_INCLUDED
#define SGE_RENDERER_TARGET_OPTIONAL_OFFSCREEN_REF_FWD_HPP_INCLUDED

#include <sge/renderer/target/offscreen_fwd.hpp>
#include <fcppt/optional/reference_fwd.hpp>

namespace sge::renderer::target
{

using optional_offscreen_ref = fcppt::optional::reference<sge::renderer::target::offscreen>;

}

#endif
