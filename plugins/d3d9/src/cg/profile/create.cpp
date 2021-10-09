//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/profile/object.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/d3d9/cg/scoped_device.hpp>
#include <sge/d3d9/cg/profile/create.hpp>
#include <sge/d3d9/cg/profile/pixel.hpp>
#include <sge/d3d9/cg/profile/vertex.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::cg::profile::object const
sge::d3d9::cg::profile::create(IDirect3DDevice9 &_device, sge::cg::profile::shader_type const _type)
{
  sge::d3d9::cg::scoped_device const context(_device);

  switch (_type)
  {
  case sge::cg::profile::shader_type::vertex:
    return sge::d3d9::cg::profile::vertex(context);
  case sge::cg::profile::shader_type::pixel:
    return sge::d3d9::cg::profile::pixel(context);
  case sge::cg::profile::shader_type::geometry:
    throw sge::renderer::unsupported(
        FCPPT_TEXT("D3D9 Cg geometry shader"), FCPPT_TEXT("D3D10"), FCPPT_TEXT(""));
  }

  FCPPT_ASSERT_UNREACHABLE;
}
