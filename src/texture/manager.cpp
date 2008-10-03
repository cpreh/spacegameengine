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


#include <sge/texture/manager.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/part.hpp>
#include <sge/renderer/image_view_dim.hpp>
#include <sge/renderer/image_view_impl.hpp>
#include <boost/foreach.hpp>

sge::texture::manager::manager(
	renderer::device_ptr const rend,
	onalloc_function const &onalloc_)
:
	rend(rend),
	onalloc_(onalloc_)
{}

sge::texture::part_ptr const
sge::texture::manager::add(
	renderer::const_image_view const &src)
{
	BOOST_FOREACH(fragmented& tex, fragmented_textures)
		if(const part_ptr p = init_texture(tex, src))
			return p;

	fragmented_textures.push_back(onalloc_());

	if(const part_ptr p = init_texture(fragmented_textures.back(), src))
		return p;
	throw image_too_big();
}

sge::texture::part_ptr const
sge::texture::manager::init_texture(
	fragmented& tex,
	renderer::const_image_view const &src) const
{
	const part_ptr p = tex.consume_fragment(
		renderer::image_view_dim(src));
	if(p)
		p->data(src);
	return p;
}

const sge::renderer::device_ptr
sge::texture::manager::get_renderer() const
{
	return rend;
}

void sge::texture::manager::onalloc(
	const onalloc_function& fun)
{
	onalloc_ = fun;
}

sge::texture::manager::image_too_big::image_too_big()
: exception(SGE_TEXT("texture::manager::add_texture() image too big!"))
{}
