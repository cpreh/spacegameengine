/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/dim2.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/color_format_fwd.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/texture/part_unique_ptr.hpp>
#include <sge/texture/rect_fragmented.hpp>
#include <sge/texture/atlasing/outer_rect.hpp>
#include <sge/texture/atlasing/size.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/move.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::texture::rect_fragmented::rect_fragmented(
	sge::renderer::device::core &_renderer,
	sge::renderer::texture::color_format const &_color_format,
	sge::renderer::texture::mipmap::object const &_mipmap,
	sge::renderer::dim2 const &_initial_size
)
:
	cur_x_(
		0u
	),
	cur_y_(
		0u
	),
	cur_height_(
		0u
	),
	texture_(
		_renderer.create_planar_texture(
			sge::renderer::texture::planar_parameters(
				_initial_size,
				_color_format,
				_mipmap,
				sge::renderer::resource_flags_field::null(),
				sge::renderer::texture::capabilities_field::null()
			)
		)
	),
	texture_count_(
		0u
	)
{
}

sge::texture::rect_fragmented::~rect_fragmented()
{
}

sge::texture::part_unique_ptr
sge::texture::rect_fragmented::consume_fragment(
	sge::renderer::dim2 const &_size
)
{
	sge::renderer::dim2 const atlased_dim(
		sge::texture::atlasing::size(
			_size
		)
	);

	// if there is no space left for the requested height
	if(
		cur_y_ + _size.h() >= texture_->size().h()
	)
		return sge::texture::part_unique_ptr();

	// if the current line is full advance to the next
	if(
		cur_x_ + _size.w() >= texture_->size().w()
	)
	{
		cur_x_ = 0;
		cur_y_ += cur_height_;
		cur_height_ = 0;
	}

	if(
		cur_y_ + _size.h() >= texture_->size().h()
	)
		return sge::texture::part_unique_ptr();

	sge::texture::part_unique_ptr ret(
		fcppt::make_unique_ptr<
			sge::texture::part_fragmented
		>(
			fcppt::ref(
				*this
			),
			sge::texture::atlasing::outer_rect(
				sge::renderer::lock_rect(
					sge::renderer::lock_rect::vector(
						cur_x_,
						cur_y_
					),
					atlased_dim
				)
			)
		)
	);

	cur_x_ += _size.w() + 1;

	cur_height_ = std::max(cur_height_, _size.h());

	++texture_count_;

	return
		fcppt::move(
			ret
		);
}

void
sge::texture::rect_fragmented::return_fragment(
	sge::texture::part const &
)
{
	--texture_count_;
}

sge::renderer::texture::planar &
sge::texture::rect_fragmented::texture()
{
	return
		*texture_;
}

sge::renderer::texture::planar const &
sge::texture::rect_fragmented::texture() const
{
	return
		*texture_;
}

bool
sge::texture::rect_fragmented::repeatable() const
{
	return
		false;
}

bool
sge::texture::rect_fragmented::empty() const
{
	return
		texture_count_ == 0u;
}
