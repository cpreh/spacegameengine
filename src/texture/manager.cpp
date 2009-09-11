/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/texture/image_too_big.hpp>
#include <sge/image/view/dim.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/variant/apply_unary.hpp>
#include <sge/text.hpp>
#include <boost/next_prior.hpp>

namespace
{

sge::texture::part_ptr const
init_texture(
	sge::texture::fragmented &,
	sge::image::view::const_object const &src);

class move_visitor {
public:
	typedef void result_type;

	move_visitor(
		sge::texture::fragmented const &,
		sge::texture::detail::fragmented_list &,
		sge::texture::detail::fragmented_queue &);
	
	result_type
	operator()(
		sge::texture::detail::fragmented_list::iterator) const;
	
	result_type
	operator()(
		sge::texture::detail::fragmented_queue::iterator) const;
private:
	sge::texture::fragmented const &tex;
	sge::texture::detail::fragmented_list &full_textures;
	sge::texture::detail::fragmented_queue &free_textures;
};

}

sge::texture::manager::manager(
	renderer::device_ptr const rend,
	onalloc_function const &onalloc_)
:
	rend(rend),
	onalloc_(onalloc_)
{}

sge::texture::manager::~manager()
{}

sge::texture::part_ptr const
sge::texture::manager::add(
	image::view::const_object const &src)
{
	for(
		detail::fragmented_queue::iterator it = free_textures.begin();
		it != free_textures.end();
		++it
	)
		if(part_ptr const p = init_texture(*it, src))
		{
			if(it->full())
			{
				fragmented *const tmp(
					&*it);

				full_textures.transfer(
					full_textures.end(),
					it,
					free_textures
				);

				tmp->container_position(
					boost::prior(
						full_textures.end()
					)
				);
			}
			return p;
		}

	fragmented_auto_ptr ntex(
		onalloc_());

	part_ptr const p = init_texture(
		*ntex,
		src);
	
	if(!p)
		throw image_too_big();
	
	fragmented *const tmp(
		ntex.get());
	
	if(ntex->full())
		tmp->container_position(
			full_textures.insert(
				full_textures.end(),
				ntex
			)
		);
	else
		tmp->container_position(
			free_textures.insert(
				ntex
			)
		);
	return p;
}

sge::renderer::device_ptr const
sge::texture::manager::renderer() const
{
	return rend;
}

void sge::texture::manager::onalloc(
	onalloc_function const &fun)
{
	onalloc_ = fun;
}

void
sge::texture::manager::free_empty_textures()
{
	for(
		detail::fragmented_queue::iterator it(
			free_textures.begin()
		),
		next(
			it
		);
		it != free_textures.end();
		it = next
	)
	{
		++next;

		if(
			it->empty()
		)

			free_textures.erase(
				it
			);
	}
}

void
sge::texture::manager::part_freed(
	detail::container_position const &pos,
	fragmented const &frag)
{	
	variant::apply_unary(
		move_visitor(
			frag,
			full_textures,
			free_textures),
		pos
	);
}

namespace
{

sge::texture::part_ptr const
init_texture(
	sge::texture::fragmented &tex,
	sge::image::view::const_object const &src)
{
	sge::texture::part_ptr const p(
		tex.consume_fragment(
			sge::image::view::dim(
				src
			)
		)
	);

	if(p)
		p->data(src);
	return p;
}


move_visitor::move_visitor(
	sge::texture::fragmented const &tex,
	sge::texture::detail::fragmented_list &full_textures,
	sge::texture::detail::fragmented_queue &free_textures)
:
	tex(tex),
	full_textures(full_textures),
	free_textures(free_textures)
{}

void move_visitor::operator()(
	sge::texture::detail::fragmented_list::iterator const it) const
{
	if(tex.empty())
		full_textures.erase(it);
	else
		free_textures.transfer(
			it,
			full_textures
		);
}

void move_visitor::operator()(
	sge::texture::detail::fragmented_queue::iterator const it) const
{
	if(tex.empty())
		free_textures.erase(it);
}

}
