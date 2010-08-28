/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/texture/atlasing/create_texture.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sge::renderer::texture_ptr const
sge::texture::atlasing::create_texture(
	renderer::device_ptr const _rend,
	image::color::format::type const _format,
	renderer::filter::texture const &_filter,
	renderer::dim_type const &_dim
)
{
	return _rend->create_texture(
		_dim,
		_format,
		_filter,
		renderer::resource_flags::none
	);
}
