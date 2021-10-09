//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/render_context/scoped_target.hpp>
#include <sge/d3d9/target/base.hpp>

sge::d3d9::render_context::scoped_target::scoped_target(sge::d3d9::target::base &_target)
    : target_(_target)
{
  target_.active(true);
}

sge::d3d9::render_context::scoped_target::~scoped_target() { target_.active(false); }

sge::d3d9::target::base &sge::d3d9::render_context::scoped_target::target() const
{
  return target_;
}
