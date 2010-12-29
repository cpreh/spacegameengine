/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/sprite/parameters_decl.hpp>
#include <sge/sprite/texture_dim.hpp>
#include <sge/sprite/roles/use_rotation.hpp>
#include <sge/image/color/init.hpp>
#include <sge/image/color/object.hpp>

template<
	typename Choices
>
sge::sprite::parameters<Choices>::parameters()
:
	elements_()
{}

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
		this->set<
			roles::pos
		>(
			_pos
		)
		.set<
			detail::roles::use_center
		>(
			false
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
		roles::texture
	>::type const &_texture
)
{
	return
		this->set<
			roles::texture
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
		this->size(
			sprite::texture_dim<
				typename Choices::type_choices::unit_type
			>()
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
sge::sprite::parameters<Choices>::default_color()
{
	return
		this->color(
			typename sge::image::color::object<
				typename Choices::type_choices::color_type
			>::type(
				(sge::image::color::init::red %= 1.0)
				(sge::image::color::init::green %= 1.0)
				(sge::image::color::init::blue %= 1.0)
				(sge::image::color::init::alpha %= 1.0)
			)
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
sge::sprite::parameters<Choices>::visible(
	typename majutsu::role_return_type<
		flattened_types,
		roles::visible
	>::type const &_visible
)
{
	return
		this->set<
			roles::visible
		>(
			_visible
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
sge::sprite::parameters<Choices>::order(
	typename majutsu::role_return_type<
		flattened_types,
		roles::order
	>::type const &_order
)
{
	return
		this->set<
			roles::order
		>(
			_order
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::adder(
	typename majutsu::role_return_type<
		flattened_types,
		roles::adder
	>::type const &_adder
)
{
	return
		this->set<
			roles::adder
		>(
			_adder
		);
}

template<
	typename Choices
>
sge::sprite::parameters<Choices> &
sge::sprite::parameters<Choices>::system(
	typename sprite::system<
		Choices
	>::type *const _system
)
{
	return
		this->set<
			roles::adder
		>(
			_system->adder()
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
typename sge::sprite::parameters<Choices>::elements_type const &
sge::sprite::parameters<Choices>::elements() const
{
	return elements_;
}

#endif
