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


#include <sge/charconv/system_fwd.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/src/cegui/prefix.hpp>
#include <sge/src/cegui/texture_parameters.hpp>


sge::cegui::texture_parameters::texture_parameters(
	sge::cegui::prefix const &_prefix,
	sge::charconv::system &_charconv_system,
	sge::image2d::system &_image_system,
	sge::renderer::device::ffp &_renderer,
	sge::renderer::texture::emulate_srgb::type const _emulate_srgb
)
:
	prefix_(
		_prefix
	),
	charconv_system_(
		_charconv_system
	),
	image_system_(
		_image_system
	),
	renderer_(
		_renderer
	),
	emulate_srgb_(
		_emulate_srgb
	)
{
}

sge::cegui::prefix const &
sge::cegui::texture_parameters::prefix() const
{
	return
		prefix_;
}

sge::charconv::system &
sge::cegui::texture_parameters::charconv_system() const
{
	return
		charconv_system_;
}

sge::image2d::system &
sge::cegui::texture_parameters::image_system() const
{
	return
		image_system_;
}

sge::renderer::device::ffp &
sge::cegui::texture_parameters::renderer() const
{
	return
		renderer_;
}

sge::renderer::texture::emulate_srgb::type
sge::cegui::texture_parameters::emulate_srgb() const
{
	return
		emulate_srgb_;
}
