/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/texture/sub_data.hpp>
#include <sge/texture/atlasing/border_h.hpp>
#include <sge/texture/atlasing/border_w.hpp>
#include <sge/texture/atlasing/make_inner_rect.hpp>
#include <sge/texture/atlasing/outer_rect.hpp>


sge::texture::part_fragmented::part_fragmented(
	sge::texture::fragmented &_fragment,
	sge::texture::atlasing::outer_rect const &_outer_area
)
:
	fragment_(
		_fragment
	),
	inner_area_(
		sge::texture::atlasing::make_inner_rect(
			_outer_area
		)
	)
{
}

sge::texture::part_fragmented::~part_fragmented()
{
	fragment_.return_fragment(
		*this
	);
}

void
sge::texture::part_fragmented::data(
	sge::image2d::view::const_object const &_src,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	sge::texture::sub_data(
		this->texture(),
		_src,
		inner_area_.get().pos(),
		_uninitialized
	);

	sge::texture::atlasing::border_h(
		this->texture(),
		_src,
		inner_area_,
		_uninitialized
	);

	sge::texture::atlasing::border_w(
		this->texture(),
		_src,
		inner_area_,
		_uninitialized
	);
}

sge::renderer::lock_rect
sge::texture::part_fragmented::area() const
{
	return
		inner_area_.get();
}

sge::renderer::texture::planar &
sge::texture::part_fragmented::texture() const
{
	return
		fragment_.texture();
}

bool
sge::texture::part_fragmented::repeatable() const
{
	return
		false;
}
