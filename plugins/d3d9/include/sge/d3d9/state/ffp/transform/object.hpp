//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_FFP_TRANSFORM_OBJECT_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_TRANSFORM_OBJECT_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/transform/object_fwd.hpp>
#include <sge/d3d9/state/ffp/transform/state.hpp>
#include <sge/renderer/state/ffp/transform/mode_fwd.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{
namespace transform
{

class object : public sge::renderer::state::ffp::transform::object
{
  FCPPT_NONCOPYABLE(object);

public:
  object(IDirect3DDevice9 &, sge::d3d9::state::ffp::transform::state const &);

  ~object();

  void set(sge::renderer::state::ffp::transform::mode) const;

private:
  IDirect3DDevice9 &device_;

  sge::d3d9::state::ffp::transform::state const state_;
};

}
}
}
}
}

#endif
