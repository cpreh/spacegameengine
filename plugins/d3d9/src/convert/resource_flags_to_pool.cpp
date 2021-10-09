//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/resource_flags_to_pool.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <fcppt/container/bitfield/operators.hpp>

D3DPOOL
sge::d3d9::convert::resource_flags_to_pool(sge::renderer::resource_flags_field const &_flags)
{
  return _flags & sge::renderer::resource_flags::dynamic ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;
}
