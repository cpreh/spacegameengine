/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/color/format.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/image_too_big.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/on_alloc_callback.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

}

sge::texture::manager::manager(
	sge::texture::on_alloc_callback const &_on_alloc
)
:
	on_alloc_(
		_on_alloc
	),
	textures_()
{
}

sge::texture::manager::~manager()
{
}

sge::texture::part_unique_ptr
sge::texture::manager::add(
	sge::image2d::view::const_object const &_src
)
{
	sge::image::color::format const color_format(
		sge::image2d::view::format(
			_src
		)
	);

	auto const init_texture(
		[
			&_src
		](
			sge::texture::fragmented &_tex
		)
		-> sge::texture::part_unique_ptr
		{
			sge::texture::part_unique_ptr part(
				_tex.consume_fragment(
					sge::image2d::view::size(
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

			return
				std::move(
					part
				);
		}
	);

	for(
		auto const &element
		:
		boost::make_iterator_range(
			textures_.equal_range(
				color_format
			)
		)
	)
		if(
			sge::texture::part_unique_ptr current_part =
				init_texture(
					*element.second
				)
		)
			return
				std::move(
					current_part
				);

	sge::texture::fragmented &new_tex(
		*textures_.insert(
			std::make_pair(
				color_format,
				on_alloc_(
					color_format
				)
			)
		)->second
	);

	sge::texture::part_unique_ptr new_part(
		init_texture(
			new_tex
		)
	);

	if(
		!new_part
	)
		throw sge::texture::image_too_big(
			sge::image2d::view::size(
				_src
			)
		);

	return
		std::move(
			new_part
		);
}

void
sge::texture::manager::on_alloc(
	sge::texture::on_alloc_callback const &_on_alloc
)
{
	on_alloc_ =
		_on_alloc;
}

void
sge::texture::manager::free_empty_textures()
{
	for(
		sge::texture::manager::fragmented_map::iterator it(
			textures_.begin()
		),
		next(
			it
		);
		it != textures_.end();
		it = next
	)
	{
		++next;

		if(
			it->second->empty()
		)
			textures_.erase(
				it
			);
	}
}
