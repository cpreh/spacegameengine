//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_SINGLE_DEVICE_SYSTEM_OPTIONAL_RENDERER_HPP_INCLUDED
#define SGE_OPENCL_SINGLE_DEVICE_SYSTEM_OPTIONAL_RENDERER_HPP_INCLUDED

#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/optional/reference.hpp>

namespace sge::opencl::single_device_system
{

using optional_renderer = fcppt::optional::reference<sge::renderer::device::core>;

}

#endif
