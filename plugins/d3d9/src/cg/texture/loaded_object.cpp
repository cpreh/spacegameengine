//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/cg/texture/assigned_stage.hpp>
#include <sge/d3d9/cg/texture/loaded_object.hpp>
#include <sge/d3d9/cg/texture/set.hpp>
#include <sge/d3d9/texture/base.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/stage.hpp>


sge::d3d9::cg::texture::loaded_object::loaded_object(
	IDirect3DDevice9 &_device,
	sge::cg::parameter::object const &_parameter,
	sge::renderer::texture::base &_texture,
	sge::renderer::caps::texture_stages const _texture_stages
)
:
	device_(
		_device
	),
	parameter_(
		_parameter
	),
	texture_(
		dynamic_cast<
			sge::d3d9::texture::base const &
		>(
			_texture
		)
	),
	texture_stages_(
		_texture_stages
	)
{
}

sge::d3d9::cg::texture::loaded_object::~loaded_object()
{
}

sge::renderer::texture::stage const
sge::d3d9::cg::texture::loaded_object::activate() const
{
	sge::d3d9::cg::texture::set(
		device_,
		parameter_,
		&texture_.get()
	);

	return
		sge::d3d9::cg::texture::assigned_stage(
			device_,
			texture_,
			texture_stages_
		);
}

void
sge::d3d9::cg::texture::loaded_object::deactivate() const
{
	sge::d3d9::cg::texture::set(
		device_,
		parameter_,
		nullptr
	);
}
