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


#include <sge/opengl/context/device/base.hpp>
#include <sge/opengl/context/device/id.hpp>
#include <sge/opengl/context/device/make_id.hpp>
#include <sge/opengl/texture/address_mode/context.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/container/index_map_impl.hpp>


sge::opengl::texture::address_mode::context::context()
:
	sge::opengl::context::device::base(),
	modes_()
{
}

sge::opengl::texture::address_mode::context::~context()
{
}

sge::renderer::state::core::sampler::address::parameters const &
sge::opengl::texture::address_mode::context::get(
	sge::renderer::texture::stage const _stage
)
{
	return
		this->get_mutable(
			_stage
		);
}

bool
sge::opengl::texture::address_mode::context::set(
	sge::renderer::texture::stage const _stage,
	sge::renderer::state::core::sampler::address::parameters const &_parameters
)
{
	sge::renderer::state::core::sampler::address::parameters &current(
		this->get_mutable(
			_stage
		)
	);

	if(
		current
		==
		_parameters
	)
		return false;

	current = _parameters;

	return true;
}

sge::renderer::state::core::sampler::address::parameters const &
sge::opengl::texture::address_mode::context::get_mutable(
	sge::renderer::texture::stage const _stage
)
{
	return
		modes_.get_default(
			_stage.get(),
			sge::renderer::state::core::sampler::address::mode_default()
		);
}

sge::opengl::context::device::id const
sge::opengl::texture::address_mode::context::static_id(
	sge::opengl::context::device::make_id()
);
