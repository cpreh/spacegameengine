//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/set_texture.hpp>
#include <sge/d3d9/texture/base.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/const.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe.hpp>


void
sge::d3d9::devicefuncs::set_texture(
	IDirect3DDevice9 &_device,
	sge::renderer::texture::stage const _stage,
	sge::renderer::texture::const_optional_base_ref const &_opt_texture
)
{
	if(
		_device.SetTexture(
			static_cast<
				DWORD
			>(
				_stage.get()
			),
			fcppt::optional::maybe(
				_opt_texture,
				fcppt::const_<
					IDirect3DBaseTexture9 *
				>(
					nullptr
				),
				[](
					fcppt::reference<
						sge::renderer::texture::base const
					> const _texture
				)
				{
					return
						&dynamic_cast<
							sge::d3d9::texture::base const &
						>(
							_texture.get()
						).get();
				}
			)
		)
		!=
		D3D_OK
	)
		throw
			sge::renderer::exception{
				FCPPT_TEXT("SetTexture() failed!")
			};
}
