//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_TEXTURE_DEPTH_STENCIL_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_DEPTH_STENCIL_HPP_INCLUDED

#if 0
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/texture/basic.hpp>
#include <sge/d3d9/texture/depth_stencil_basic.hpp>
#include <sge/renderer/depth_stencil_surface_unique_ptr.hpp>
#include <sge/renderer/texture/depth_stencil.hpp>
#include <sge/renderer/texture/depth_stencil_parameters.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{


class depth_stencil
:
	public texture::depth_stencil_basic
{
	FCPPT_NONCOPYABLE(
		depth_stencil
	);
public:
	depth_stencil(
		IDirect3DDevice9 *,
		renderer::texture::depth_stencil_parameters const &
	);

	~depth_stencil();

	dim const
	size() const;

	renderer::depth_stencil_surface_ptr const
	surface() const;
};


}
}
}
#endif

#endif
