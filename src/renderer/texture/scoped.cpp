/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/device.hpp>
#include <sge/renderer/stage.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <sge/renderer/texture/const_optional_base.hpp>
#include <sge/renderer/texture/scoped.hpp>


sge::renderer::texture::scoped::scoped(
	renderer::device &_device,
	renderer::texture::base const &_texture,
	renderer::stage const _stage
)
:
	device_(_device),
	stage_(_stage)
{
	device_.texture(
		_texture,
		stage_
	);
}

sge::renderer::texture::scoped::~scoped()
{
	device_.texture(
		renderer::texture::const_optional_base(),
		stage_
	);
}
