/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/activate.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/bind_context.hpp>
#include <sge/opengl/texture/bind_level.hpp>
#include <sge/opengl/texture/disable.hpp>
#include <sge/opengl/texture/enable.hpp>
#include <sge/opengl/texture/get_stage_type.hpp>
#include <sge/opengl/texture/optional_id.hpp>
#include <sge/opengl/texture/optional_type.hpp>
#include <sge/opengl/texture/render_binding.hpp>
#include <sge/opengl/texture/set_samplers.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/const_optional_base_ref.hpp>
#include <sge/renderer/texture/stage.hpp>


void
sge::opengl::texture::activate(
	sge::opengl::context::system::object &_system_context,
	sge::opengl::context::device::object &_device_context,
	sge::renderer::texture::const_optional_base_ref const &_texture,
	sge::renderer::texture::stage const _stage
)
{
	sge::opengl::texture::active_level const active_level(
		_system_context,
		_stage
	);

	sge::opengl::texture::bind_context &bind_context(
		sge::opengl::context::use<
			sge::opengl::texture::bind_context
		>(
			_device_context
		)
	);

	{
		sge::opengl::texture::optional_type const old_type(
			sge::opengl::texture::get_stage_type(
				_device_context,
				_stage
			)
		);

		if(
			old_type
		)
		{
			sge::opengl::texture::disable(
				active_level,
				*old_type
			);

			if(
				!_texture
			)
			{
				sge::opengl::texture::bind_level(
					active_level,
					*old_type,
					sge::opengl::texture::optional_id()
				);

				bind_context.stage(
					_stage,
					sge::opengl::texture::const_optional_base_ref()
				);
			}
		}
	}

	if(
		!_texture
	)
		return;

	sge::opengl::texture::base const &base(
		dynamic_cast<
			sge::opengl::texture::base const &
		>(
			*_texture
		)
	);

	sge::opengl::texture::enable(
		active_level,
		base.type()
	);

	bind_context.stage(
		_stage,
		sge::opengl::texture::const_optional_base_ref(
			base
		)
	);

	sge::opengl::texture::bind_level(
		active_level,
		base.type(),
		sge::opengl::texture::optional_id(
			base.id()
		)
	);

	sge::opengl::texture::render_binding const binding(
		active_level,
		base.type()
	);

	sge::opengl::texture::set_samplers(
		binding,
		_system_context,
		_device_context
	);
}
