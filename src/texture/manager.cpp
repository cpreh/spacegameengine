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


#include <sge/texture/manager.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/image_too_big.hpp>
#include <sge/image2d/view/dim.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <fcppt/container/ptr/insert_unique_ptr.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_multiset.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/text.hpp>
#include <boost/next_prior.hpp>

namespace
{

sge::texture::part_ptr const
init_texture(
	sge::texture::fragmented &,
	sge::image2d::view::const_object const &
);

class move_visitor
{
	FCPPT_NONASSIGNABLE(
		move_visitor
	);
public:
	typedef void result_type;

	move_visitor(
		sge::texture::fragmented const &,
		sge::texture::detail::fragmented_list &,
		sge::texture::detail::fragmented_queue &
	);

	result_type
	operator()(
		sge::texture::detail::fragmented_list::iterator
	) const;

	result_type
	operator()(
		sge::texture::detail::fragmented_queue::iterator
	) const;
private:
	sge::texture::fragmented const &tex_;

	sge::texture::detail::fragmented_list &full_textures_;

	sge::texture::detail::fragmented_queue &free_textures_;
};

}

sge::texture::manager::manager(
	renderer::device_ptr const _rend,
	on_alloc_function const &_on_alloc
)
:
	rend_(_rend),
	on_alloc_(_on_alloc)
{}

sge::texture::manager::~manager()
{}

sge::texture::part_ptr const
sge::texture::manager::add(
	image2d::view::const_object const &_src
)
{
	for(
		detail::fragmented_queue::iterator it = free_textures_.begin();
		it != free_textures_.end();
		++it
	)
		if(
			part_ptr const current_part =
				init_texture(
					*it,
					_src
				)
		)
		{
			if(
				it->full()
			)
			{
				fragmented *const tmp(
					&*it
				);

				full_textures_.transfer(
					full_textures_.end(),
					it,
					free_textures_
				);

				tmp->container_position(
					boost::prior(
						full_textures_.end()
					)
				);
			}
			return current_part;
		}

	fragmented_unique_ptr ntex(
		on_alloc_()
	);

	part_ptr const new_part(
		init_texture(
			*ntex,
			_src
		)
	);

	if(
		!new_part
	)
		throw texture::image_too_big();

	fragmented *const tmp(
		ntex.get()
	);

	if(
		ntex->full()
	)
		tmp->container_position(
			fcppt::container::ptr::insert_unique_ptr(
				full_textures_,
				full_textures_.end(),
				move(
					ntex
				)
			)
		);
	else
		tmp->container_position(
			fcppt::container::ptr::insert_unique_ptr_multiset(
				free_textures_,
				move(
					ntex
				)
			)
		);

	return new_part;
}

sge::renderer::device_ptr const
sge::texture::manager::renderer() const
{
	return rend_;
}

void
sge::texture::manager::on_alloc(
	on_alloc_function const &_on_alloc
)
{
	on_alloc_ = _on_alloc;
}

void
sge::texture::manager::free_empty_textures()
{
	for(
		detail::fragmented_queue::iterator it(
			free_textures_.begin()
		),
		next(
			it
		);
		it != free_textures_.end();
		it = next
	)
	{
		++next;

		if(
			it->empty()
		)

			free_textures_.erase(
				it
			);
	}
}

void
sge::texture::manager::part_freed(
	detail::container_position const &_pos,
	fragmented const &_frag
)
{
	fcppt::variant::apply_unary(
		::move_visitor(
			_frag,
			full_textures_,
			free_textures_
		),
		_pos
	);
}

namespace
{

sge::texture::part_ptr const
init_texture(
	sge::texture::fragmented &_tex,
	sge::image2d::view::const_object const &_src
)
{
	sge::texture::part_ptr const part(
		_tex.consume_fragment(
			sge::image2d::view::dim(
				_src
			)
		)
	);

	if(
		part
	)
		part->data(
			_src
		);

	return part;
}


move_visitor::move_visitor(
	sge::texture::fragmented const &_tex,
	sge::texture::detail::fragmented_list &_full_textures,
	sge::texture::detail::fragmented_queue &_free_textures
)
:
	tex_(_tex),
	full_textures_(_full_textures),
	free_textures_(_free_textures)
{}

void
move_visitor::operator()(
	sge::texture::detail::fragmented_list::iterator const _it
) const
{
	if(
		tex_.empty()
	)
		full_textures_.erase(
			_it
		);
	else
		free_textures_.transfer(
			_it,
			full_textures_
		);
}

void
move_visitor::operator()(
	sge::texture::detail::fragmented_queue::iterator const _it
) const
{
	if(
		tex_.empty()
	)
		free_textures_.erase(
			_it
		);
}

}
