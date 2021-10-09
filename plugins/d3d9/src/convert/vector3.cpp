//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/vector3.hpp>
#include <sge/renderer/vector3.hpp>

D3DVECTOR
sge::d3d9::convert::vector3(sge::renderer::vector3 const &_vec)
{
  return D3DVECTOR{_vec.x(), _vec.y(), _vec.z()};
}
