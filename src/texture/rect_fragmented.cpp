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


#include <sge/texture/rect_fragmented.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/texture/atlasing/create.hpp>
#include <sge/texture/atlasing/size.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

sge::texture::rect_fragmented::rect_fragmented(
	renderer::device &_rend,
	image::color::format::type const _format,
	renderer::texture::mipmap::object const &_mipmap,
	renderer::dim2 const &_initial_size
)
:
	cur_x_(0),
	cur_y_(0),
	cur_height_(0),
	tex_(
		atlasing::create(
			_rend,
			_format,
			_mipmap,
			_initial_size
		)
	),
	texture_count_(0)
{
}

sge::texture::rect_fragmented::~rect_fragmented()
{
}

sge::texture::part_ptr const
sge::texture::rect_fragmented::consume_fragment(
	renderer::dim2 const &_size
)
{
	renderer::texture::planar::dim const atlased_dim(
		atlasing::size(
			_size,
			true
		)
	);

	// if there is no space left for the requested height
	if(
		cur_y_ + _size.h() >= tex_->size().h()
	)
		return texture::part_ptr();

	// if the current line is full advance to the next
	if(
		cur_x_ + _size.w() >= tex_->size().w()
	)
	{
		cur_x_ = 0;
		cur_y_ += cur_height_;
		cur_height_ = 0;
	}

	if(
		cur_y_ + _size.h() >= tex_->size().h()
	)
		return texture::part_ptr();

	texture::part_ptr const ret(
		fcppt::make_shared_ptr<
			texture::part_fragmented
		>(
			renderer::lock_rect(
				renderer::lock_rect::vector(
					cur_x_,
					cur_y_
				),
				atlased_dim
			),
			fcppt::ref(
				*this
			),
			true,
			true
		)
	);

	cur_x_ += _size.w() + 1;

	cur_height_ = std::max(cur_height_, _size.h());

	++texture_count_;

	return ret;
}

void
sge::texture::rect_fragmented::on_return_fragment(
	part const &
)
{
	--texture_count_;
}

sge::renderer::texture::planar_ptr const
sge::texture::rect_fragmented::texture()
{
	return tex_;
}

sge::renderer::texture::const_planar_ptr const
sge::texture::rect_fragmented::texture() const
{
	return tex_;
}

bool
sge::texture::rect_fragmented::repeatable() const
{
	return false;
}

sge::texture::free_type
sge::texture::rect_fragmented::free_value() const
{
	return
		static_cast<
			free_type
		>(
			(this->texture()->size().h() - cur_height_)
			* this->texture()->size().w()
		);
}

bool
sge::texture::rect_fragmented::empty() const
{
	return !texture_count_;
}
