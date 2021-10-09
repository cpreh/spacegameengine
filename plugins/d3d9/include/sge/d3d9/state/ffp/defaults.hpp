//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_FFP_DEFAULTS_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_DEFAULTS_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/defaults_fwd.hpp>
#include <sge/d3d9/state/ffp/alpha_test/object_fwd.hpp>
#include <sge/d3d9/state/ffp/alpha_test/object_unique_ptr.hpp>
#include <sge/d3d9/state/ffp/fog/object_fwd.hpp>
#include <sge/d3d9/state/ffp/fog/object_unique_ptr.hpp>
#include <sge/d3d9/state/ffp/lighting/object_fwd.hpp>
#include <sge/d3d9/state/ffp/lighting/object_unique_ptr.hpp>
#include <sge/d3d9/state/ffp/lighting/material/object_fwd.hpp>
#include <sge/d3d9/state/ffp/lighting/material/object_unique_ptr.hpp>
#include <sge/d3d9/state/ffp/misc/object_fwd.hpp>
#include <sge/d3d9/state/ffp/misc/object_unique_ptr.hpp>
#include <sge/d3d9/state/ffp/sampler/object_fwd.hpp>
#include <sge/d3d9/state/ffp/sampler/object_unique_ptr.hpp>
#include <sge/d3d9/state/ffp/transform/object_fwd.hpp>
#include <sge/d3d9/state/ffp/transform/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{

class defaults
{
  FCPPT_NONCOPYABLE(defaults);

public:
  explicit defaults(IDirect3DDevice9 &);

  ~defaults();

  sge::d3d9::state::ffp::alpha_test::object const &alpha_test() const;

  sge::d3d9::state::ffp::fog::object const &fog() const;

  sge::d3d9::state::ffp::lighting::object const &lighting() const;

  sge::d3d9::state::ffp::lighting::material::object const &material() const;

  sge::d3d9::state::ffp::misc::object const &misc() const;

  sge::d3d9::state::ffp::sampler::object const &sampler() const;

  sge::d3d9::state::ffp::transform::object const &transform() const;

private:
  sge::d3d9::state::ffp::alpha_test::object_unique_ptr const alpha_test_;

  sge::d3d9::state::ffp::fog::object_unique_ptr const fog_;

  sge::d3d9::state::ffp::lighting::object_unique_ptr const lighting_;

  sge::d3d9::state::ffp::lighting::material::object_unique_ptr const material_;

  sge::d3d9::state::ffp::misc::object_unique_ptr const misc_;

  sge::d3d9::state::ffp::sampler::object_unique_ptr const sampler_;

  sge::d3d9::state::ffp::transform::object_unique_ptr const transform_;
};

}
}
}
}

#endif
