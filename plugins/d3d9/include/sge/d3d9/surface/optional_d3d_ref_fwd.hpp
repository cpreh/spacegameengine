//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_SURFACE_OPTIONAL_D3D_REF_FWD_HPP_INCLUDED
#define SGE_D3D9_SURFACE_OPTIONAL_D3D_REF_FWD_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <fcppt/optional/reference_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace surface
{

typedef
fcppt::optional::reference<
	IDirect3DSurface9
>
optional_d3d_ref;

}
}
}

#endif
