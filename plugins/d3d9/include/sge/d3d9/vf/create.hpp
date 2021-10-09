//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_VF_CREATE_HPP_INCLUDED
#define SGE_D3D9_VF_CREATE_HPP_INCLUDED

#include <sge/d3d9/vf/element_vector.hpp>
#include <sge/d3d9/vf/texture_coordinate_count.hpp>
#include <sge/renderer/vf/dynamic/format_fwd.hpp>

namespace sge
{
namespace d3d9
{
namespace vf
{

sge::d3d9::vf::element_vector
create(sge::renderer::vf::dynamic::format const &, sge::d3d9::vf::texture_coordinate_count);

}
}
}

#endif
