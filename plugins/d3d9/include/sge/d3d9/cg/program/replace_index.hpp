//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_CG_PROGRAM_REPLACE_INDEX_HPP_INCLUDED
#define SGE_D3D9_CG_PROGRAM_REPLACE_INDEX_HPP_INCLUDED

#include <sge/cg/string.hpp>
#include <sge/cg/program/extra_index.hpp>
#include <sge/d3d9/vf/texture_coordinate_count.hpp>

namespace sge
{
namespace d3d9
{
namespace cg
{
namespace program
{

sge::cg::string
    replace_index(sge::d3d9::vf::texture_coordinate_count, sge::cg::program::extra_index);

}
}
}
}

#endif
