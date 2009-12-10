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
	typename Choices,
	typename Elements
>
sge::sprite::object<Choices, Elements>::object(
	element_type const &nelements_
)
:
	elements_(
		detail::transform_init_arguments<
			Choices,
			Elements
		>(
			nelements_
		)
	)
{}

template<
	typename Choices,
	typename Elements
>
sge::sprite::object<Choices, Elements>::object(
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
	typename Choices,
	typename Elements
>
sge::sprite::object<Choices, Elements> &
sge::sprite::object<Choices, Elements>::operator=(
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
	typename Choices,
	typename Elements
>
typename sge::sprite::object<Choices, Elements>::unit
sge::sprite::object<Choices, Elements>::x() const
{
	return pos().x();
}

template<
	typename Choices,
	typename Elements
>
typename sge::sprite::object<Choices, Elements>::unit
sge::sprite::object<Choices, Elements>::y() const
{
	return pos().y();
}

template<
	typename Choices,
	typename Elements
>
typename sge::sprite::object<Choices, Elements>::point const
sge::sprite::object<Choices, Elements>::pos() const
{
	return
		elements_. template get<
			roles::pos
		>();
}

template<
	typename Choices,
	typename Elements
>
typename sge::sprite::object<Choices, Elements>::unit
sge::sprite::object<Choices, Elements>::w() const
{
	return size().w();
}

template<
	typename Choices,
	typename Elements
>
typename sge::sprite::object<Choices, Elements>::unit
sge::sprite::object<Choices, Elements>::h() const
{
	return size().h();
}

template<
	typename Choices,
	typename Elements
>
typename sge::sprite::object<Choices, Elements>::dim const
sge::sprite::object<Choices, Elements>::size() const
{
	return
		elements_. template get<
			roles::size
		>();
}

template<
	typename Choices,
	typename Elements
>
typename sge::sprite::object<Choices, Elements>::depth_type
sge::sprite::object<Choices, Elements>::z() const
{
	return
		elements_. template get<
			roles::depth
		>();
}

template<
	typename Choices,
	typename Elements
>
bool
sge::sprite::object<Choices, Elements>::visible() const
{
	return
		elements_. template get<
			roles::visible
		>();
}

template<
	typename Choices,
	typename Elements
>
typename sge::sprite::object<Choices, Elements>::rotation_type
sge::sprite::object<Choices, Elements>::rotation() const
{
	return
		elements_. template get<
			roles::rotation
		>();
}

template<
	typename Choices,
	typename Elements
>
typename sge::sprite::object<Choices, Elements>::point const
sge::sprite::object<Choices, Elements>::rotation_center() const
{
	return
		detail::rotation_center(
			*this
		);

}

template<
	typename Choices,
	typename Elements
>
typename sge::sprite::object<Choices, Elements>::repetition_type
sge::sprite::object<Choices, Elements>::repeat() const
{
	return
		elements_. template get<
			roles::repetition
		>();
}

template<
	typename Choices,
	typename Elements
>
typename sge::sprite::object<Choices, Elements>::color_type  const
sge::sprite::object<Choices, Elements>::color() const
{
	return
		elements_. template get<
			roles::color
		>();
}

template<
	typename Choices,
	typename Elements
>
sge::texture::const_part_ptr const
sge::sprite::object<Choices, Elements>::texture() const
{
	return
		elements_. template get<
			roles::texture
		>();
}

template<
	typename Choices,
	typename Elements
>
typename sge::sprite::object<Choices, Elements>::order_type
sge::sprite::object<Choices, Elements>::order() const
{
	return
		elements_. template get<
			roles::order
		>();
}

template<
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::x(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::y(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::z(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::pos(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::w(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::h(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::size(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::visible(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::texture(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::rotation(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::rotate_around(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::reset_rotation()
{
	elements_. template set<
		roles::use_rotation
	>(
		false
	);
}

template<
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::repeat(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::color(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::order(
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
	typename Choices,
	typename Elements
>
void
sge::sprite::object<Choices, Elements>::transfer(
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
	typename Choices,
	typename Elements
>
template<
	typename Role
>
typename majutsu::role_return_type<
	typename sge::sprite::object<
		Choices,
		Elements
	>::flattened_types,
	Role
>::type
sge::sprite::object<Choices, Elements>::get() const
{
	return
		elements_. template get<
			Role
		>();
}

template<
	typename Choices,
	typename Elements
>
template<
	typename Role
>
void
sge::sprite::object<Choices, Elements>::set(
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
