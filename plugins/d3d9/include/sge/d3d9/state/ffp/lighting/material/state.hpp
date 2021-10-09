//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_FFP_LIGHTING_MATERIAL_STATE_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_LIGHTING_MATERIAL_STATE_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/ffp/lighting/material/state_fwd.hpp>

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

class state
{
public:
  explicit state(D3DMATERIAL9 const &);

  D3DMATERIAL9 const &material() const;

private:
  D3DMATERIAL9 material_;
};

}
}
}
}
}
}

#endif
