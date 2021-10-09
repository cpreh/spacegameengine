//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/sampler/create.hpp>
#include <sge/d3d9/state/ffp/sampler/make_states.hpp>
#include <sge/d3d9/state/ffp/sampler/object.hpp>
#include <sge/renderer/state/ffp/sampler/object.hpp>
#include <sge/renderer/state/ffp/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/sampler/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sge::renderer::state::ffp::sampler::object_unique_ptr sge::d3d9::state::ffp::sampler::create(
    IDirect3DDevice9 &_device, sge::renderer::state::ffp::sampler::parameters const &_parameters)
{
  return fcppt::unique_ptr_to_base<sge::renderer::state::ffp::sampler::object>(
      fcppt::make_unique_ptr<sge::d3d9::state::ffp::sampler::object>(
          _device, sge::d3d9::state::ffp::sampler::make_states(_parameters)));
}
