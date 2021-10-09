//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/fog/create_default.hpp>
#include <sge/d3d9/state/ffp/fog/make_states.hpp>
#include <sge/d3d9/state/ffp/fog/object.hpp>
#include <sge/d3d9/state/ffp/fog/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/fog/default.hpp>
#include <sge/renderer/state/ffp/fog/parameters.hpp>
#include <fcppt/make_unique_ptr.hpp>

sge::d3d9::state::ffp::fog::object_unique_ptr
sge::d3d9::state::ffp::fog::create_default(IDirect3DDevice9 &_device)
{
  return fcppt::make_unique_ptr<sge::d3d9::state::ffp::fog::object>(
      _device, sge::d3d9::state::ffp::fog::make_states(sge::renderer::state::ffp::fog::default_()));
}
