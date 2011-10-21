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


#include <sge/font/text/drawer_3d.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/renderer/caps.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/default_equal.hpp>
#include <sge/sprite/default_sort.hpp>
#include <sge/sprite/external_system_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/parameters_impl.hpp>
#include <sge/sprite/render_states.hpp>
#include <sge/texture/rect_fragmented.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/dim/quad.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/phoenix/object/construct.hpp>
#include <boost/spirit/home/phoenix/object/new.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::font::text::drawer_3d::drawer_3d(
	renderer::device &_rend,
	sge::image::color::any::object const &_col
)
:
	col_(_col),
	texman_(
		boost::phoenix::construct<
			texture::fragmented_unique_ptr
		>(
			boost::phoenix::new_<
				texture::rect_fragmented
			>(
				fcppt::ref(
					_rend
				),
				_rend.caps().preferred_texture_format(),
				renderer::texture::mipmap::off(),
				fcppt::math::dim::quad<
					renderer::dim2
				>(
					256
				)
			)
		)
	),
	sys_(_rend),
	sprites_()
{}

sge::font::text::drawer_3d::~drawer_3d()
{}

void
sge::font::text::drawer_3d::begin_rendering(
	size_type const buffer_chars,
	pos const &,
	dim const &
)
{
	sprites_.clear();

	sprites_.reserve(
		buffer_chars
	);
}

void
sge::font::text::drawer_3d::draw_char(
	text::char_type const _char,
	pos const &_pos,
	const_image_view const &_data
)
{
	sge::image2d::dim const dim(
		sge::image2d::view::size(
			_data
		)
	);

	typedef sge::sprite::parameters<
		sprite_choices
	> sprite_parameters;

	sprites_.push_back(
		sprite_object(
			sprite_parameters()
			.pos(
				_pos
			)
			.texture(
				dim.content()
				?
					cached_texture(
						_char,
						_data
					)
				:
					texture::const_part_ptr()
			)
			.size(
				fcppt::math::dim::structure_cast<
					sprite_object::dim
				>(
					dim
				)
			)
			.color(
				// TODO:
				image::color::any::convert<
					sprite_object::color_format
				>(
					col_
				)
			)
			.elements()
		)
	);
}

void
sge::font::text::drawer_3d::end_rendering()
{
	sys_.render(
		sprites_.begin(),
		sprites_.end(),
		sprite::default_sort(),
		sprite::default_equal()
	);
}

void
sge::font::text::drawer_3d::color(
	sge::image::color::any::object const &_col
)
{
	col_ = _col;
}

sge::texture::const_part_ptr const
sge::font::text::drawer_3d::cached_texture(
	text::char_type const _ch,
	const_image_view const &_data
)
{
	texture_map::const_iterator const it(
		textures_.find(
			_ch
		)
	);

	return
		it != textures_.end()
		?
			it->second
		:
			textures_.insert(
				std::make_pair(
					_ch,
					texman_.add(
						_data
					)
				)
			).first->second;
}
