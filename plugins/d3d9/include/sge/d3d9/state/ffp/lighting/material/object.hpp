//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_FFP_LIGHTING_MATERIAL_OBJECT_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_LIGHTING_MATERIAL_OBJECT_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/lighting/material/object_fwd.hpp>
#include <sge/d3d9/state/ffp/lighting/material/state.hpp>
#include <sge/renderer/state/ffp/lighting/material/object.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{
namespace lighting
{
namespace material
{

class object : public sge::renderer::state::ffp::lighting::material::object
{
  FCPPT_NONCOPYABLE(object);

public:
  object(IDirect3DDevice9 &, sge::d3d9::state::ffp::lighting::material::state const &);

  ~object();

  void set() const;

private:
  IDirect3DDevice9 &device_;

  sge::d3d9::state::ffp::lighting::material::state const state_;
};

}
}
}
}
}
}

#endif
