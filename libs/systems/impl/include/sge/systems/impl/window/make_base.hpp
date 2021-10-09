//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_IMPL_WINDOW_MAKE_BASE_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_MAKE_BASE_HPP_INCLUDED

#include <sge/systems/window_fwd.hpp>
#include <sge/systems/impl/renderer/optional_system_ref_fwd.hpp>
#include <sge/systems/impl/window/base_unique_ptr.hpp>
#include <sge/window/system_ref.hpp>

namespace sge::systems::impl::window
{

sge::systems::impl::window::base_unique_ptr make_base(
    sge::systems::window const &,
    sge::window::system_ref,
    sge::systems::impl::renderer::optional_system_ref const &);

}

#endif
