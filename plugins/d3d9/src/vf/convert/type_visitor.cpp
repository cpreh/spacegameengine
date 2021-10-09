//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vf/convert/color_type.hpp>
#include <sge/d3d9/vf/convert/extra_type.hpp>
#include <sge/d3d9/vf/convert/type_visitor.hpp>
#include <sge/d3d9/vf/convert/vector_type.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <sge/renderer/vf/dynamic/element_type.hpp>
#include <sge/renderer/vf/dynamic/extra_fwd.hpp>
#include <sge/renderer/vf/dynamic/normal.hpp>
#include <sge/renderer/vf/dynamic/pos.hpp>
#include <sge/renderer/vf/dynamic/texpos.hpp>
#include <fcppt/text.hpp>

sge::d3d9::vf::convert::type_visitor::result_type
sge::d3d9::vf::convert::type_visitor::operator()(sge::renderer::vf::dynamic::pos const &_pos) const
{
  return sge::d3d9::vf::convert::vector_type(_pos.type());
}

sge::d3d9::vf::convert::type_visitor::result_type sge::d3d9::vf::convert::type_visitor::operator()(
    sge::renderer::vf::dynamic::normal const &_normal) const
{
  if (_normal.element_type() != sge::renderer::vf::dynamic::element_type::float_)
    throw sge::renderer::unsupported(
        FCPPT_TEXT("D3D9 only supports normals with a float element type!"),
        FCPPT_TEXT(""),
        FCPPT_TEXT(""));

  return D3DDECLTYPE_FLOAT3;
}

sge::d3d9::vf::convert::type_visitor::result_type sge::d3d9::vf::convert::type_visitor::operator()(
    sge::renderer::vf::dynamic::color const &_color) const
{
  return sge::d3d9::vf::convert::color_type(_color);
}

sge::d3d9::vf::convert::type_visitor::result_type sge::d3d9::vf::convert::type_visitor::operator()(
    sge::renderer::vf::dynamic::texpos const &_texpos) const
{
  return sge::d3d9::vf::convert::vector_type(_texpos.type());
}

sge::d3d9::vf::convert::type_visitor::result_type sge::d3d9::vf::convert::type_visitor::operator()(
    sge::renderer::vf::dynamic::extra const &_extra) const
{
  return sge::d3d9::vf::convert::extra_type(_extra);
}
