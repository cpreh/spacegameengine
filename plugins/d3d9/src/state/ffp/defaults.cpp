//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/defaults.hpp>
#include <sge/d3d9/state/ffp/alpha_test/create_default.hpp>
#include <sge/d3d9/state/ffp/alpha_test/object.hpp>
#include <sge/d3d9/state/ffp/fog/create_default.hpp>
#include <sge/d3d9/state/ffp/fog/object.hpp>
#include <sge/d3d9/state/ffp/lighting/create_default.hpp>
#include <sge/d3d9/state/ffp/lighting/object.hpp>
#include <sge/d3d9/state/ffp/lighting/material/create_default.hpp>
#include <sge/d3d9/state/ffp/lighting/material/object.hpp>
#include <sge/d3d9/state/ffp/misc/create_default.hpp>
#include <sge/d3d9/state/ffp/misc/object.hpp>
#include <sge/d3d9/state/ffp/sampler/create_default.hpp>
#include <sge/d3d9/state/ffp/sampler/object.hpp>
#include <sge/d3d9/state/ffp/transform/create_default.hpp>
#include <sge/d3d9/state/ffp/transform/object.hpp>

sge::d3d9::state::ffp::defaults::defaults(IDirect3DDevice9 &_device)
    : alpha_test_(sge::d3d9::state::ffp::alpha_test::create_default(_device)),
      fog_(sge::d3d9::state::ffp::fog::create_default(_device)),
      lighting_(sge::d3d9::state::ffp::lighting::create_default(_device)),
      material_(sge::d3d9::state::ffp::lighting::material::create_default(_device)),
      misc_(sge::d3d9::state::ffp::misc::create_default(_device)),
      sampler_(sge::d3d9::state::ffp::sampler::create_default(_device)),
      transform_(sge::d3d9::state::ffp::transform::create_default(_device))
{
}

sge::d3d9::state::ffp::defaults::~defaults() {}

sge::d3d9::state::ffp::alpha_test::object const &sge::d3d9::state::ffp::defaults::alpha_test() const
{
  return *alpha_test_;
}

sge::d3d9::state::ffp::fog::object const &sge::d3d9::state::ffp::defaults::fog() const
{
  return *fog_;
}

sge::d3d9::state::ffp::lighting::object const &sge::d3d9::state::ffp::defaults::lighting() const
{
  return *lighting_;
}

sge::d3d9::state::ffp::lighting::material::object const &
sge::d3d9::state::ffp::defaults::material() const
{
  return *material_;
}

sge::d3d9::state::ffp::misc::object const &sge::d3d9::state::ffp::defaults::misc() const
{
  return *misc_;
}

sge::d3d9::state::ffp::sampler::object const &sge::d3d9::state::ffp::defaults::sampler() const
{
  return *sampler_;
}

sge::d3d9::state::ffp::transform::object const &sge::d3d9::state::ffp::defaults::transform() const
{
  return *transform_;
}
