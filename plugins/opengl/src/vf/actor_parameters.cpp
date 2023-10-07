//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/vf/actor_parameters.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>

sge::opengl::vf::actor_parameters::actor_parameters(
    sge::renderer::vf::dynamic::stride const _stride,
    sge::renderer::vf::dynamic::offset const _offset,
    sge::opengl::context::object_ref const _context)
    : stride_(_stride), offset_(_offset), context_(_context)
{
}

sge::renderer::vf::dynamic::stride sge::opengl::vf::actor_parameters::stride() const
{
  return stride_;
}

sge::renderer::vf::dynamic::offset sge::opengl::vf::actor_parameters::offset() const
{
  return offset_;
}

sge::opengl::context::object &sge::opengl::vf::actor_parameters::context() const
{
  return context_.get();
}
