//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_CG_PROGRAM_CREATE_LOADED_HPP_INCLUDED
#define SGE_D3D9_CG_PROGRAM_CREATE_LOADED_HPP_INCLUDED

#include <sge/cg/program/object_fwd.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/cg/loaded_program_unique_ptr.hpp>

namespace sge
{
namespace d3d9
{
namespace cg
{
namespace program
{

sge::renderer::cg::loaded_program_unique_ptr
create_loaded(IDirect3DDevice9 &, sge::cg::program::object &);

}
}
}
}

#endif
