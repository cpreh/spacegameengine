//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_VF_CONVERT_INDEX_VISITOR_HPP_INCLUDED
#define SGE_D3D9_VF_CONVERT_INDEX_VISITOR_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/vf/texture_coordinate_count.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>
#include <sge/renderer/vf/dynamic/extra_fwd.hpp>
#include <sge/renderer/vf/dynamic/normal_fwd.hpp>
#include <sge/renderer/vf/dynamic/pos_fwd.hpp>
#include <sge/renderer/vf/dynamic/texpos_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace vf
{
namespace convert
{

class index_visitor
{
public:
  explicit index_visitor(sge::d3d9::vf::texture_coordinate_count);

  typedef BYTE result_type;

  result_type operator()(sge::renderer::vf::dynamic::pos const &) const;

  result_type operator()(sge::renderer::vf::dynamic::normal const &) const;

  result_type operator()(sge::renderer::vf::dynamic::color const &) const;

  result_type operator()(sge::renderer::vf::dynamic::texpos const &) const;

  result_type operator()(sge::renderer::vf::dynamic::extra const &) const;

private:
  sge::d3d9::vf::texture_coordinate_count texture_coordinates_;
};

}
}
}
}

#endif
