//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/renderer/target/base_ref.hpp>

sge::renderer::context::scoped_ffp::scoped_ffp(
    sge::renderer::device::ffp_ref const _device, sge::renderer::target::base_ref const _target)
    : device_(_device), context_(device_.get().begin_rendering_ffp(_target))
{
}

sge::renderer::context::scoped_ffp::~scoped_ffp() { device_.get().end_rendering_ffp(*context_); }

sge::renderer::context::ffp &sge::renderer::context::scoped_ffp::get() const { return *context_; }
