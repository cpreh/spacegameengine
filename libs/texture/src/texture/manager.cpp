/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/fragmented_unique_ptr.hpp>
#include <sge/texture/image_too_big.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/on_alloc_callback.hpp>
#include <sge/texture/optional_part_unique_ptr.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_by_opt.hpp>
#include <fcppt/algorithm/map_iteration_second.hpp>
#include <fcppt/algorithm/update_action.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


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
		-> sge::texture::optional_part_unique_ptr
		{
			sge::texture::optional_part_unique_ptr part(
				_tex.consume_fragment(
					sge::image2d::view::size(
						_src
					)
				)
			);

			fcppt::optional::maybe_void(
				part,
				[
					&_src
				](
					sge::texture::part_unique_ptr const &_part
				)
				{
					_part->data(
						_src,
						sge::image::algorithm::uninitialized::yes
					);
				}
			);

			return
				part;
		}
	);


	return
		fcppt::optional::from(
			fcppt::algorithm::find_by_opt(
				boost::make_iterator_range(
					textures_.equal_range(
						color_format
					)
				),
				[
					init_texture
				](
					fragmented_map::value_type const &_element
				)
				{
					return
						init_texture(
							*_element.second
						);
				}
			),
			[
				&_src,
				color_format,
				init_texture,
				this
			]{
				return
					fcppt::optional::to_exception(
						init_texture(
							*textures_.insert(
								std::make_pair(
									color_format,
									on_alloc_(
										color_format
									)
								)
							)->second
						),
						[
							&_src
						]{
							return
								sge::texture::image_too_big(
									sge::image2d::view::size(
										_src
									)
								);
						}
					);
			}
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
	fcppt::algorithm::map_iteration_second(
		textures_,
		[](
			sge::texture::fragmented_unique_ptr const &_texture
		)
		{
			return
				_texture->empty()
				?
					fcppt::algorithm::update_action::remove
				:
					fcppt::algorithm::update_action::keep
				;
		}
	);
}
