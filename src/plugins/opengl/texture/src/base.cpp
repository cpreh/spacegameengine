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


#include "../base.hpp"
#include <sge/renderer/texture/filter/normal/mag.hpp>
#include <sge/renderer/texture/filter/normal/make.hpp>
#include <sge/renderer/texture/filter/normal/min.hpp>
#include <sge/renderer/texture/filter/normal/mip.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <sge/renderer/texture/mipmap/off_rep.hpp>
#include <fcppt/variant/holds_type.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::opengl::texture::type const
sge::opengl::texture::base::type() const
{
	return type_;
}

sge::opengl::texture::id const
sge::opengl::texture::base::id() const
{
	return holder_.id();
}

bool
sge::opengl::texture::base::update_filter(
	renderer::texture::filter::object const &_filter
) const
{
	if(
		filter_ == _filter
	)
		return false;

	filter_ = _filter;

	return true;
}

bool
sge::opengl::texture::base::has_mipmap() const
{
	return
		!fcppt::variant::holds_type<
			sge::renderer::texture::mipmap::off_rep
		>(
			this->mipmap().variant()
		);
}

sge::opengl::texture::base::~base()
{
}

sge::opengl::texture::base::base(
	texture::type const _type
)
:
	type_(_type),
	holder_(),
	filter_(
		sge::renderer::texture::filter::normal::make(
			sge::renderer::texture::filter::normal::mag::linear,
			sge::renderer::texture::filter::normal::min::point,
			sge::renderer::texture::filter::normal::mip::linear
		)
	)
{
}
