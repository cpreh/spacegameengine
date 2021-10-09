//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SYSTEMS_IMPL_RENDERER_CREATE_DEVICE_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_RENDERER_CREATE_DEVICE_HPP_INCLUDED

#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <sge/systems/impl/renderer/system_fwd.hpp>
#include <sge/systems/impl/window/object_fwd.hpp>

namespace sge::systems::impl::renderer
{

sge::renderer::device::core_unique_ptr create_device(
    sge::systems::detail::renderer const &,
    sge::systems::impl::renderer::system const &,
    sge::systems::impl::window::object const &);

}

#endif
