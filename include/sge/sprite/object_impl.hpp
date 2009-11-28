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
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/depth.hpp>
#include <sge/sprite/roles/visible.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/roles/rotate_around.hpp>
#include <sge/sprite/roles/use_rotation.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <sge/sprite/roles/order.hpp>
#include <sge/sprite/roles/system.hpp>

template<
	typename Choices,
	typename Elements
>
template<
	typename Parameters
>
sge::sprite::object<Choices, Elements>::object(
	Parameters const &parameters_
)
:
	elements(
		parameters_.elements()
	)
{}

template<
	typename Elements
>
sge::sprite::object<Elements>::object(
	object const &other_
)
:
	elements(
		other.elements
	)
{
	add_me();
}

template<
	typename Elements
>
sge::sprite::object<Element> &
sge::sprite::object<Elements>::operator=(
	object const &other_
)
{
	unlink();

	elements = other_.elements;

	detail::object_base_hook::operator=(r);	

	add_me();

	return *this;
}

template<
	typename Elements
>
sge::sprite::unit
sge::sprite::object<Elements>::x() const
{
	return pos().x();
}

template<
	typename Elements
>
sge::sprite::unit
sge::sprite::object<Elements>::y() const
{
	return pos().y();
}

template<
	typename Elements
>
sge::sprite::point const
sge::sprite::object<Elements>::pos() const
{
	return
		elements. template get<
			roles::pos
		>();
}

template<
	typename Elements
>
sge::sprite::unit
sge::sprite::object::w() const
{
	return size().w();
}

template<
	typename Elements
>
sge::sprite::unit
sge::sprite::object::h() const
{
	return size().h();
}

template<
	typename Elements
>
sge::sprite::dim
sge::sprite::object::size() const
{
	return
		elements. template get<
			roles::size
		>();
}

template<
	typename Elements
>
sge::sprite::depth_type
sge::sprite::object::z() const
{
	return
		elements. template get<
			roles::depth
		>();
}

template<
	typename Elements
>
bool
sge::sprite::object::visible() const
{
	return
		elements. template get<
			roles::visible
		>();
}

template<
	typename Elements
>
sge::sprite::rotation_type
sge::sprite::object::rotation() const
{
	return
		elements. template get<
			roles::rotation
		>();
}

template<
	typename Elements
>
sge::sprite::point const
sge::sprite::object::rotation_center() const
{
	return
		elements. template get<
			roles::use_rotation
		>()
		?
			pos()
			+ elements. template get<
				roles::rotate_around
			>()
		:
			center(
				*this
			);
}

template<
	typename Elements
>
sge::sprite::repetition_type
sge::sprite::object::repeat() const
{
	return
		elements. template get<
			roles::repetition
		>();
}

template<
	typename Elements
>
sge::sprite::color const
sge::sprite::object::color() const
{
	return
		elements. template get<
			roles::color
		>();
}

template<
	typename Elements
>
sge::texture::const_part_ptr const
sge::sprite::object<Elements>::texture() const
{
	return
		elements. template get<
			roles::texture
		>();
}

template<
	typename Elements
>
sge;:sprite::order_type
sge::sprite::object<Elements>::order() const
{
	return
		elements. template get<
			roles::order
		>();
}

template<
	typename Elements
>
void
sge::sprite::object::x(
	unit const x_
)
{
	pos(
		x_,
		y()
	);
}

template<
	typename Elements
>
void
sge::sprite::object::y(
	unit const y_
)
{
	pos(
		x(),
		y_
	);
}

template<
	typename Elements
>
void
sge::sprite::object::z(
	depth_type const depth_
) 
{
	elements. template set<
		roles::depth
	>(
		depth_
	);
}

template<
	typename Elements
>
void
sge::sprite::object::pos(
	point const &pos_
)
{
	elements. template set<
		roles::pos
	>(
		pos_
	);
}

template<
	typename Elements
>
void
sge::sprite::object::w(
	unit const w_
)
{
	size(
		w_,
		h()
	);
}

template<
	typename Elements
>
void
sge::sprite::object::h(
	unit const h_
) 
{
	return size().h();
}

template<
	typename Elements
>
void
sge::sprite::object::size(
	dim const &dim_
) 
{
	elements. template set<
		roles::dim
	>(
		dim_
	);
}

template<
	typename Elements
>
void
sge::sprite::object::visible(
	bool const visible_
)
{
	elements. template set<
		roles::visible
	>(
		visible_
	);
}

template<
	typename Elements
>
void
sge::sprite::object::texture(
	::sge::texture::const_part_ptr const texture_
)
{
	elements. template set<
		roles::texture
	>(
		texture_
	);
}

template<
	typename Elements
>
void
sge::sprite::object::rotation(
	rotation_type const rotation_
)
{
	elements. template set<
		roles::rotation
	>(
		rotation_
	);
}

template<
	typename Elements
>
void
sge::sprite::object::rotate_around(
	point const &rotate_around_
)
{
	elements. template set<
		roles::rotate_around
	>(
		rotate_around_
	);
}

template<
	typename Elements
>
void
sge::sprite::object::reset_rotation()
{
	elements. template set<
		roles::rotate_arond
	>(
		point()
	);
}

template<
	typename Elements
>
void
sge::sprite::object::repeat(
	repetition_type const repeat_
)
{
	elements. template set<
		roles::repetition
	>(
		repeat_
	);
}

template<
	typename Elements
>
void
sge::sprite::object::color(
	sprite::color const &color_
)
{
	elements. template set<
		roles::color
	>(
		color_
	);
}

template<
	typename Elements
>
void
sge::sprite::object<Elements>::order(
	order_type const order_
)
{
	unlink();

	elements. template set<
		roles::order
	>(
		order_
	);

	add_me();
}

template<
	typename Elements
>
void
sge::sprite::object<Elements>::transfer(
	system &system_
)
{
	unlink();

	elements. template set<
		roles::system
	>(
		&system_
	);

	add_me();
}

template<
	typename  Elements
>
void
sge::sprite::object<Elements>::add_me()
{
	elements. template get<
		roles::system
	>()->add(
		*this,
		order()
	);
}

#endif
