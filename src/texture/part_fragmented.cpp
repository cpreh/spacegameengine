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


#include <sge/texture/part_fragmented.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/sub_data.hpp>
#include <sge/texture/atlasing/border_w.hpp>
#include <sge/texture/atlasing/border_h.hpp>
#include <sge/texture/atlasing/inner_rect.hpp>
#include <fcppt/math/box/basic_impl.hpp>

sge::texture::part_fragmented::part_fragmented(
	renderer::lock_rect const &_outer_area,
	texture::fragmented &_fragment,
	bool const _need_atlasing_w,
	bool const _need_atlasing_h
)
:
	outer_area_(_outer_area),
	fragment_(_fragment),
	need_atlasing_w_(_need_atlasing_w),
	need_atlasing_h_(_need_atlasing_h),
	inner_area_(
		atlasing::inner_rect(
			outer_area_,
			need_atlasing_w_,
			need_atlasing_h_
		)
	)
{}

sge::texture::part_fragmented::~part_fragmented()
{
	fragment_.return_fragment(
		*this
	);
}

void
sge::texture::part_fragmented::data(
	image2d::view::const_object const &_src
)
{
	texture::sub_data(
		this->texture(),
		_src,
		inner_area_.pos()
	);

	if(
		need_atlasing_h_
	)
		atlasing::border_h(
			this->texture(),
			_src,
			outer_area_,
			inner_area_
		);

	if(
		need_atlasing_w_
	)
		atlasing::border_w(
			this->texture(),
			_src,
			outer_area_,
			inner_area_
		);
}

sge::renderer::lock_rect const &
sge::texture::part_fragmented::area() const
{
	return inner_area_;
}

sge::renderer::texture::planar &
sge::texture::part_fragmented::texture()
{
	return fragment_.texture();
}

sge::renderer::texture::planar const &
sge::texture::part_fragmented::texture() const
{
	return fragment_.texture();
}

bool
sge::texture::part_fragmented::repeatable() const
{
	return !need_atlasing_w_ && !need_atlasing_h_;
}
