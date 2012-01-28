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


#ifndef SGE_SPRITE_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/image/color/object.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/sprite/parameters_decl.hpp>
#include <sge/sprite/defaults/color.hpp>
#include <sge/sprite/detail/config/color_format.hpp>
#include <sge/sprite/detail/config/has_normal_size.hpp>
#include <sge/sprite/detail/parameters/unset_use_center.hpp>
#include <sge/sprite/detail/roles/use_center.hpp>
#include <sge/sprite/detail/roles/use_texture_size.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/connection.hpp>
#include <sge/sprite/roles/depth.hpp>
#include <sge/sprite/roles/point_size.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/repetition.hpp>
#include <sge/sprite/roles/rotate_around.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <sge/sprite/roles/texture_coordinates.hpp>
#include <sge/sprite/roles/use_rotation.hpp>
#include <majutsu/role_return_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/static_assert.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Choices
>
sge::sprite::parameters<Choices>::parameters()
:
	elements_()
{
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::pos(
	typename majutsu::role_return_type<
		flattened_types,
		roles::pos
	>::type const &_pos
)
{
	return
		sge::sprite::detail::parameters::unset_use_center(
			this->set<
				roles::pos
			>(
				_pos
			)
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::center(
	typename majutsu::role_return_type<
		flattened_types,
		roles::pos
	>::type const &_pos
)
{
	BOOST_STATIC_ASSERT(
		sge::sprite::detail::config::has_normal_size<
			Choices
		>::value
	);

	return
		this->set<
			roles::pos
		>(
			_pos
		)
		.set<
			detail::roles::use_center
		>(
			true
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::texture(
	typename majutsu::role_return_type<
		flattened_types,
		roles::texture<
			0
		>
	>::type const &_texture
)
{
	return
		this->set<
			roles::texture<
				0
			>
		>(
			_texture
		);
}

template<
	typename Choices
>
template<
	sge::sprite::texture_level Level
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::texture_level(
	typename majutsu::role_return_type<
		flattened_types,
		roles::texture<
			Level
		>
	>::type const &_texture
)
{
	return
		this->set<
			roles::texture<
				Level
			>
		>(
			_texture
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::size(
	typename majutsu::role_return_type<
		flattened_types,
		roles::size
	>::type const &_size
)
{
	return
		this->set<
			roles::size
		>(
			_size
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::point_size(
	typename majutsu::role_return_type<
		flattened_types,
		roles::point_size
	>::type const &_point_size
)
{
	return
		this->set<
			roles::point_size
		>(
			_point_size
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::texture_size()
{
	return
		this->set<
			detail::roles::use_texture_size
		>(
			true
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::color(
	typename majutsu::role_return_type<
		flattened_types,
		roles::color
	>::type const &_color
)
{
	return
		this->set<
			roles::color
		>(
			_color
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::any_color(
	sge::image::color::any::object const &_color
)
{
	return
		this->color(
			sge::image::color::any::convert<
				typename sge::sprite::detail::config::color_format<
					Choices
				>::type
			>(
				_color
			)
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::default_color()
{
	return
		this->color(
			sprite::defaults<
				Choices,
				roles::color
			>::get()
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::depth(
	typename majutsu::role_return_type<
		flattened_types,
		roles::depth
	>::type const &_depth
)
{
	return
		this->set<
			roles::depth
		>(
			_depth
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::rotation(
	typename majutsu::role_return_type<
		flattened_types,
		roles::rotation
	>::type const &_rotation
)
{
	return
		this->set<
			roles::rotation
		>(
			_rotation
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::no_rotation_point()
{
	return
		this->set<
			roles::use_rotation
		>(
			false
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::rotation_point(
	typename majutsu::role_return_type<
		flattened_types,
		roles::rotate_around
	>::type const &_rotation_point
)
{
	return
		this->set<
			roles::rotate_around
		>(
			_rotation_point
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::repetition(
	typename majutsu::role_return_type<
		flattened_types,
		roles::repetition
	>::type const &_repetition
)
{
	return
		this->set<
			roles::repetition
		>(
			_repetition
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::texture_coordinates(
	typename majutsu::role_return_type<
		flattened_types,
		roles::texture_coordinates<
			0
		>
	>::type const &_texture_coordinates
)
{
	return
		this->set<
			roles::texture_coordinates<
				0
			>
		>(
			_texture_coordinates
		);
}

template<
	typename Choices
>
template<
	sge::sprite::texture_level Level
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::texture_coordinates_level(
	typename majutsu::role_return_type<
		flattened_types,
		roles::texture_coordinates<
			Level
		>
	>::type const &_texture_coordinates
)
{
	return
		this->set<
			roles::texture_coordinates<
				Level
			>
		>(
			_texture_coordinates
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::connection(
	typename majutsu::role_return_type<
		flattened_types,
		roles::connection
	>::type const &_connection
)
{
	return
		this->set<
			roles::connection
		>(
			_connection
		);
}

template<
	typename Choices
>
template<
	typename Role
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::set(
	typename majutsu::role_return_type<
		flattened_types,
		Role
	>::type const &_value
)
{
	elements_. template set<
		Role
	>(
		_value
	);

	return *this;
}

template<
	typename Choices
>
template<
	typename Role
>
typename majutsu::role_return_type<
	typename sge::sprite::parameters<
		Choices
	>::flattened_types,
	Role
>::type const
sge::sprite::parameters<Choices>::get() const
{
	return
		elements_. template get<
			Role
		>();
}

template<
	typename Choices
>
typename sge::sprite::parameters<Choices>::elements_type const &
sge::sprite::parameters<Choices>::elements() const
{
	return elements_;
}

#endif
