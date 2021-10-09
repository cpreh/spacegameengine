//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_RENDER_HPP_INCLUDED
#define SGE_D3D9_STATE_RENDER_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/render_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace state
{

class render
{
public:
  render(D3DRENDERSTATETYPE, DWORD);

  D3DRENDERSTATETYPE
  state() const;

  DWORD
  value() const;

private:
  D3DRENDERSTATETYPE state_;

  DWORD value_;
};

}
}
}

#endif
