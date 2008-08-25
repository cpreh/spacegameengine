/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/create_texture.hpp>
#include <sge/renderer/image_view_impl.hpp>

sge::renderer::texture_ptr const
sge::image::create_texture(
	renderer::device_ptr const r,
	object_ptr const p,
	renderer::filter_args const &filter,
	renderer::resource_flag_t const flags)
{
	return r->create_texture(
		p->view(),
		filter,
		flags);
}

sge::renderer::texture_ptr const
sge::image::create_texture(
	path const &file,
	renderer::device_ptr const r,
	loader_ptr const p,
	renderer::filter_args const &filter,
	renderer::resource_flag_t const flags)
{
	return create_texture(
		r,
		p->load_image(file),
		filter,
		flags);
}
