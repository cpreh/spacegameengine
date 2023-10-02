//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_VIEWPORT_IMPL_MAINTAIN_ASPECT_FUNCTION_HPP_INCLUDED
#define SGE_VIEWPORT_IMPL_MAINTAIN_ASPECT_FUNCTION_HPP_INCLUDED

#include <sge/renderer/target/viewport.hpp>
#include <sge/viewport/fractional_aspect.hpp>
#include <awl/window/event/resize_fwd.hpp>

namespace sge::viewport::impl
{

sge::renderer::target::viewport
maintain_aspect_function(awl::window::event::resize const &, sge::viewport::fractional_aspect);

}

#endif
