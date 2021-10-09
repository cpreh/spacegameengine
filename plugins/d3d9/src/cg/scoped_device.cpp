//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/cg/get_device.hpp>
#include <sge/d3d9/cg/scoped_device.hpp>
#include <sge/d3d9/cg/set_device.hpp>

sge::d3d9::cg::scoped_device::scoped_device(IDirect3DDevice9 &_device)
    : old_(sge::d3d9::cg::get_device()), needs_reset_(old_ != &_device)
{
  if (needs_reset_)
    sge::d3d9::cg::set_device(&_device);
}

sge::d3d9::cg::scoped_device::~scoped_device()
{
  if (needs_reset_)
    sge::d3d9::cg::set_device(old_);
}
