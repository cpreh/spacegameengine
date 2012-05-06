/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/cg/texture/assigned_stage.hpp>
#include <sge/d3d9/cg/texture/loaded_object.hpp>
#include <sge/d3d9/cg/texture/set.hpp>
#include <sge/d3d9/texture/base.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/null_ptr.hpp>


sge::d3d9::cg::texture::loaded_object::loaded_object(
	IDirect3DDevice9 *const _device,
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
		texture_.get()
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
		fcppt::null_ptr()
	);
}
