/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/sprite/detail/rotation_center.hpp>
#include <sge/sprite/detail/assign_pre.hpp>
#include <sge/sprite/detail/assign_post.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/depth.hpp>
#include <sge/sprite/roles/visible.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/roles/rotate_around.hpp>
#include <sge/sprite/roles/use_rotation.hpp>
#include <sge/sprite/roles/repetition.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <sge/sprite/roles/order.hpp>
#include <sge/sprite/roles/system.hpp>

template<
	typename Choices
>
sge::sprite::object<Choices>::object(
	element_type const &nelements_
)
:
	elements_(
		detail::transform_init_arguments<
			Choices
		>(
			nelements_
		)
	)
{}

template<
	typename Choices
>
sge::sprite::object<Choices>::object(
	object const &other_
)
:
	elements_(
		other_.elements_
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
	object const &other_
)
{
	detail::assign_pre(
		*this,
		other_
	);

	elements_ = other_.elements_;

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
typename sge::sprite::object<Choices>::point const
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
typename sge::sprite::object<Choices>::point const
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
sge::sprite::object<Choices>::repeat() const
{
	return
		elements_. template get<
			roles::repetition
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
	unit const x_
)
{
	pos(
		point(
			x_,
			y()
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::y(
	unit const y_
)
{
	pos(
		point(
			x(),
			y_
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::z(
	depth_type const depth_
) 
{
	elements_. template set<
		roles::depth
	>(
		depth_
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::pos(
	point const &pos_
)
{
	elements_. template set<
		roles::pos
	>(
		pos_
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::w(
	unit const w_
)
{
	size(
		dim(
			w_,
			h()
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::h(
	unit const h_
) 
{
	size(
		dim(
			w(),
			h_
		)
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::size(
	dim const &dim_
) 
{
	elements_. template set<
		roles::size
	>(
		dim_
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::visible(
	bool const visible_
)
{
	elements_. template set<
		roles::visible
	>(
		visible_
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::texture(
	::sge::texture::const_part_ptr const texture_
)
{
	elements_. template set<
		roles::texture
	>(
		texture_
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::rotation(
	rotation_type const rotation_
)
{
	elements_. template set<
		roles::rotation
	>(
		rotation_
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::rotate_around(
	point const &rotate_around_
)
{
	elements_. template set<
		roles::rotate_around
	>(
		rotate_around_
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
	repetition_type const repeat_
)
{
	elements_. template set<
		roles::repetition
	>(
		repeat_
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::color(
	color_type const &color_
)
{
	elements_. template set<
		roles::color
	>(
		color_
	);
}

template<
	typename Choices
>
void
sge::sprite::object<Choices>::order(
	order_type const order_
)
{
	intrusive::detail::object_base_hook::unlink();

	elements_. template set<
		roles::order
	>(
		order_
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
	system &system_
)
{
	intrusive::detail::object_base_hook::unlink();

	elements_. template set<
		roles::system
	>(
		&system_
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
	>::type const &value_
)
{
	elements_. template set<
		Role
	>(
		value_
	);
}

#endif
