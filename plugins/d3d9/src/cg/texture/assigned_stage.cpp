//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/cg/texture/assigned_stage.hpp>
#include <sge/d3d9/com/compare_ptr.hpp>
#include <sge/d3d9/devicefuncs/get_texture.hpp>
#include <sge/d3d9/texture/base.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::renderer::texture::stage const
sge::d3d9::cg::texture::assigned_stage(
	IDirect3DDevice9 &_device,
	sge::d3d9::texture::base const &_texture,
	sge::renderer::caps::texture_stages const _max_stages
)
{
	for(
		sge::renderer::texture::stage stage(
			0u
		);
		stage.get() < _max_stages.get();
		++stage
	)
		if(
			sge::d3d9::com::compare_ptr(
				sge::d3d9::devicefuncs::get_texture(
					_device,
					stage
				).get(),
				&_texture.get()
			)
		)
			return
				stage;

	FCPPT_ASSERT_UNREACHABLE;
}
