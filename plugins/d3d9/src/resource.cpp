//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/needs_reset.hpp>
#include <sge/d3d9/resource.hpp>

sge::d3d9::resource::resource(D3DPOOL const _pool) : pool_(_pool) {}

sge::d3d9::resource::resource(sge::d3d9::needs_reset const _needs_reset)
    : pool_(_needs_reset == sge::d3d9::needs_reset::yes ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED)
{
}

sge::d3d9::resource::~resource() {}

void sge::d3d9::resource::loss()
{
  if (this->needs_reset())
    this->on_loss();
}

void sge::d3d9::resource::reset()
{
  if (this->needs_reset())
    this->on_reset();
}

D3DPOOL
sge::d3d9::resource::pool() const { return pool_; }

bool sge::d3d9::resource::needs_reset() const { return this->pool() != D3DPOOL_MANAGED; }
