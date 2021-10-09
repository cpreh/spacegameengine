//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vf/convert/role_visitor.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <sge/renderer/vf/dynamic/extra_fwd.hpp>
#include <sge/renderer/vf/dynamic/normal_fwd.hpp>
#include <sge/renderer/vf/dynamic/pos_fwd.hpp>
#include <sge/renderer/vf/dynamic/texpos_fwd.hpp>

sge::d3d9::vf::convert::role_visitor::result_type
sge::d3d9::vf::convert::role_visitor::operator()(sge::renderer::vf::dynamic::pos const &) const
{
  return D3DDECLUSAGE_POSITION;
}

sge::d3d9::vf::convert::role_visitor::result_type
sge::d3d9::vf::convert::role_visitor::operator()(sge::renderer::vf::dynamic::normal const &) const
{
  return D3DDECLUSAGE_NORMAL;
}

sge::d3d9::vf::convert::role_visitor::result_type
sge::d3d9::vf::convert::role_visitor::operator()(sge::renderer::vf::dynamic::color const &) const
{
  return D3DDECLUSAGE_COLOR;
}

sge::d3d9::vf::convert::role_visitor::result_type
sge::d3d9::vf::convert::role_visitor::operator()(sge::renderer::vf::dynamic::texpos const &) const
{
  return D3DDECLUSAGE_TEXCOORD;
}

sge::d3d9::vf::convert::role_visitor::result_type
sge::d3d9::vf::convert::role_visitor::operator()(sge::renderer::vf::dynamic::extra const &) const
{
  return D3DDECLUSAGE_TEXCOORD;
}
