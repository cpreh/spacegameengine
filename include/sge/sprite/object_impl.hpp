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


#ifndef SGE_SPRITE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SPRITE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/detail/transform_init_arguments.hpp>
#include <sge/sprite/detail/transform_parameters_arguments.hpp>
#include <sge/sprite/detail/rotation_center.hpp>
#include <sge/sprite/detail/assign_pre.hpp>
#include <sge/sprite/detail/assign_post.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/point_size.hpp>
#include <sge/sprite/roles/depth.hpp>
#include <sge/sprite/roles/visible.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/roles/rotate_around.hpp>
#include <sge/sprite/roles/use_rotation.hpp>
#include <sge/sprite/roles/repetition.hpp>
#include <sge/sprite/roles/texture_coordinates.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <sge/sprite/roles/order.hpp>
#include <sge/sprite/roles/adder.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

template<
	typename Choices
>
sge::sprite::object<Choices>::object()
:
	elements_()
{}

template<
	typename Choices
>
sge::sprite::object<Choices>::object(
	element_type const &_elements
)
:
	elements_(
		detail::transform_init_arguments<
			Choices
		>(
			_elements
		)
	)
{
	detail::assign_post(
		*this
	);
}

template<
	typename Choices
>
template<
	typename Parameters
>
sge::sprite::object<Choices>::object(
	Parameters const &_parameters
)
:
	elements_(
		detail::transform_parameters_arguments<
			element_type,
			Choices
		>(
			_parameters
		)
	)
{
	detail::assign_post(
		*this
	);
}

template<
	typename Choices
>
sge::sprite::object<Choices>::object(
	object const &_other
)
:
	elements_(
		_other.elements_
	)
{
	detail::assign_post(
		*this
	);
}

template<
	typename Choices
>
sge::sprite::object<Choices> &
sge::sprite::object<Choices>::operator=(
	object const &_other
)
{
	detail::assign_pre(
		*this,
		_other
	);

	elements_ = _other.elements_;

	detail::assign_post(
		*this
	);

	return *this;
}

template<
	typename Choices
>
sge::sprite::object<Choices>::~object()
{}

template<
	typename Choices
>
typename sge::sprite::object<Choices>::unit
sge::sprite::object<Choices>::x() const
{
	return pos().x();
}

template<
	typename Choices
>
typename sge::sprite::object<Choices>::unit
sge::sprite::object<Choices>::y() const
{
	return pos().y();
}

template<
	typename Choices
>
typename sge::sprite::object<Choices>::vector const
sge::sprite::object<Choices>::pos() const
{
	return
		elements_. template get<
			roles::pos
		>();
}

template<
	typename Choices
>
typename sge::sprite::object<Choices>::unit
sge::sprite::object<Choices>::w() const
{
	return size().w();
}

template<
	typename Choices
>
typename sge::sprite::object<Choices>::unit
sge::sprite::object<Choices>::h() const
{
	return size().h();
}

template<
	typename Choices
>
typename sge::sprite::object<Choices>::dim const
sge::sprite::object<Choices>::size() const
{
	return
		elements_. template get<
			roles::size
		>();
}

template<
	typename Choices
>
typename sge::sprite::object<Choices>::point_size_type
sge::sprite::object<Choices>::point_size() const
{
	return
		elements_. template get<
			roles::point_size
		>();
}

template<
	typename Choices
>
typename sge::sprite::object<Choices>::depth_type
sge::sprite::object<Choices>::z() const
{
	return
		elements_. template get<
			roles::depth
		>();
}

template<
	typename Choices
>
bool
sge::sprite::object<Choices>::visible() const
{
	return
		elements_. template get<
			roles::visible
		>();
}

template<
	typename Choices
>
typename sge::sprite::object<Choices>::rotation_type
sge::sprite::object<Choices>::rotation() const
{
	return
		elements_. template get<
			roles::rotation
		>();
}

template<
	typename Choices
>
typename sge::sprite::object<Choices>::vector const
sge::sprite::object<Choices>::rotation_center() const
{
	return
		detail::rotation_center(
			*this
		);

}

template<
	typename Choices
>
typename sge::sprite::object<Choices>::repetition_type
sge::sprite::object<Choices>::repetition() const
{
	return
		elements_. template get<
			roles::repetition
		>();
}

template<
	typename Choices
>
typename sge::sprite::object<Choices>::texture_coordinates_type const
sge::sprite::object<Choices>::texture_coordinates() const
{
	return
		elements_. template get<
			roles::texture_coordinates
		>();
}


template<
	typename Choices
>
typename sge::sprite::object<Choices>::color_type  const
sge::sprite::object<Choices>::color() const
{
	return
		elements_. template get<
			roles::color
		>();
}

template<
	typename Choices
>
sge::texture::const_part_ptr const
sge::sprite::object<Choices>::texture() const
{
	return
		elements_. template get<
			roles::texture
		>();
}

template<
	typename Choices
>
typename sge::sprite::object<Choices>::order_type
sge::sprite::object<Choices>::order() const
{
	return
		elements_. template get<
			roles::order
		>();
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::x(
	unit const _x
)
{
	pos(
		vector(
			_x,
			y()
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::y(
	unit const _y
)
{
	pos(
		vector(
			x(),
			_y
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::z(
	depth_type const _depth
)
{
	elements_. template set<
		roles::depth
	>(
		_depth
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::pos(
	vector const &_pos
)
{
	elements_. template set<
		roles::pos
	>(
		_pos
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::w(
	unit const _w
)
{
	size(
		dim(
			_w,
			h()
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::h(
	unit const _h
)
{
	size(
		dim(
			w(),
			_h
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::size(
	dim const &_dim
)
{
	elements_. template set<
		roles::size
	>(
		_dim
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::point_size(
	point_size_type const _point_size
)
{
	elements_. template set<
		roles::point_size
	>(
		_point_size
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::visible(
	bool const _visible
)
{
	elements_. template set<
		roles::visible
	>(
		_visible
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::texture(
	::sge::texture::const_part_ptr const _texture
)
{
	elements_. template set<
		roles::texture
	>(
		_texture
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::rotation(
	rotation_type const _rotation
)
{
	elements_. template set<
		roles::rotation
	>(
		_rotation
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::rotate_around(
	vector const &_rotate_around
)
{
	elements_. template set<
		roles::rotate_around
	>(
		_rotate_around
	);

	elements_. template set<
		roles::use_rotation
	>(
		true
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::reset_rotation()
{
	elements_. template set<
		roles::use_rotation
	>(
		false
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::repeat(
	repetition_type const _repeat
)
{
	elements_. template set<
		roles::repetition
	>(
		_repeat
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::texture_coordinates(
	texture_coordinates_type const &_coordinates
)
{
	elements_. template set<
		roles::texture_coordinates
	>(
		_coordinates
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::color(
	color_type const &_color
)
{
	elements_. template set<
		roles::color
	>(
		_color
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::order(
	order_type const _order
)
{
	intrusive::detail::object_base_hook::unlink();

	elements_. template set<
		roles::order
	>(
		_order
	);

	detail::assign_post(
		*this
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::transfer(
	system &_system
)
{
	intrusive::detail::object_base_hook::unlink();

	elements_. template set<
		roles::adder
	>(
		_system.adder()
	);

	detail::assign_post(
		*this
	);
}

template<
	typename Choices
>
template<
	typename Role
>
typename majutsu::role_return_type<
	typename sge::sprite::object<
		Choices
	>::flattened_types,
	Role
>::type
sge::sprite::object<Choices>::get() const
{
	return
		elements_. template get<
			Role
		>();
}

template<
	typename Choices
>
template<
	typename Role
>
void
sge::sprite::object<Choices>::set(
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
}

#endif
