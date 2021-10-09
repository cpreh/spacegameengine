//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_VIEWPORT_IMPL_CENTER_HPP_INCLUDED
#define SGE_VIEWPORT_IMPL_CENTER_HPP_INCLUDED

#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/window/dim.hpp>

namespace sge::viewport::impl
{

sge::renderer::target::viewport
center(sge::window::dim const &ref_dim, sge::window::dim const &window_dim);

}

#endif
