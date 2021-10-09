//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_VERTEX_D3D_DECLARATION_UNIQUE_PTR_HPP_INCLUDED
#define SGE_D3D9_VERTEX_D3D_DECLARATION_UNIQUE_PTR_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sge
{
namespace d3d9
{
namespace vertex
{

typedef fcppt::unique_ptr<IDirect3DVertexDeclaration9, fcppt::com_deleter>
    d3d_declaration_unique_ptr;

}
}
}

#endif
