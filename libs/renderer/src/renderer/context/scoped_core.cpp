//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/scoped_core.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/target/base_ref.hpp>

sge::renderer::context::scoped_core::scoped_core(
    sge::renderer::device::core_ref const _device, sge::renderer::target::base_ref const _target)
    : device_(_device), context_(device_.get().begin_rendering(_target))
{
}

sge::renderer::context::scoped_core::~scoped_core() { device_.get().end_rendering(*context_); }

sge::renderer::context::core &sge::renderer::context::scoped_core::get() const { return *context_; }
