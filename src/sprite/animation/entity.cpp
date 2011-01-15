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


#include <sge/sprite/animation/entity.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/chrono/duration_impl.hpp>

sge::sprite::animation::entity::entity(
	time::duration const &_res,
	texture::const_part_ptr const _tex
)
:
	delay_(_res.count()),
	tex_(_tex)
{}

sge::time::unit
sge::sprite::animation::entity::delay() const
{
	return delay_;
}

sge::texture::const_part_ptr const
sge::sprite::animation::entity::tex() const
{
	return tex_;
}

void
sge::sprite::animation::entity::tex(
	texture::const_part_ptr const _tex
)
{
	tex_ = _tex;
}

sge::renderer::dim2 const
sge::sprite::animation::entity::dim() const
{
	return tex_->area().dimension();
}
