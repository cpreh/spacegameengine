//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/get_texture.hpp>
#include <sge/d3d9/texture/d3d_base_texture_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/text.hpp>


sge::d3d9::texture::d3d_base_texture_unique_ptr
sge::d3d9::devicefuncs::get_texture(
	IDirect3DDevice9 &_device,
	sge::renderer::texture::stage const _stage
)
{
	IDirect3DBaseTexture9 *result;

	if(
		_device.GetTexture(
			_stage.get(),
			&result
		)
		!=
		D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("GetTexture failed!")
		);

	return
		sge::d3d9::texture::d3d_base_texture_unique_ptr(
			result
		);
}
