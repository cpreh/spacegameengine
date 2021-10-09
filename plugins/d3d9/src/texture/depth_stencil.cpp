//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/texture/depth_stencil.hpp>
#include <fcppt/math/dim/object_impl.hpp>

#if 0
sge::d3d9::texture::depth_stencil::depth_stencil(
	IDirect3DDevice9 *const _device,
	renderer::texture::depth_stencil_parameters const &_params
)
:
	texture::depth_stencil_basic(
		_device,
		_params
	)
{
}

sge::d3d9::texture::depth_stencil::~depth_stencil()
{
}

sge::d3d9::texture::depth_stencil::dim const
sge::d3d9::texture::depth_stencil::size() const
{
	return this->parameters().size();
}


sge::renderer::depth_stencil_surface_ptr const
sge::d3d9::texture::depth_stencil::surface() const
{
	return renderer::depth_stencil_surface_ptr();
}
#endif
