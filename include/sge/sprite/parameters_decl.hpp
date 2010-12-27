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


#ifndef SGE_SPRITE_PARAMETERS_DECL_HPP_INCLUDED
#define SGE_SPRITE_PARAMETERS_DECL_HPP_INCLUDED

#include <sge/sprite/parameters_fwd.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/detail/roles/use_center.hpp>
#include <sge/sprite/detail/make_class.hpp>
#include <sge/sprite/roles/adder.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/depth.hpp>
#include <sge/sprite/roles/order.hpp>
#include <sge/sprite/roles/point_size.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/repetition.hpp>
#include <sge/sprite/roles/rotation.hpp>
#include <sge/sprite/roles/rotate_around.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <sge/sprite/roles/visible.hpp>
#include <majutsu/role_return_type.hpp>
#include <majutsu/role.hpp>
#include <majutsu/fundamental.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sge
{
namespace sprite
{

template<
	typename Choices
>
class parameters
{
	typedef typename detail::make_class<
		Choices,
		boost::mpl::vector1<
			majutsu::role<
				majutsu::fundamental<
					bool
				>,
				detail::roles::use_center
			>
		>
	>::type elements_type;

	typedef typename elements_type::memory_type::types flattened_types;
public:
	parameters();

	parameters const
	pos(
		typename majutsu::role_return_type<
			flattened_types,
			roles::pos
		>::type const &
	) const;

	parameters const
	center(
		typename majutsu::role_return_type<
			flattened_types,
			roles::pos
		>::type const &
	) const;

	parameters const
	texture(
		typename majutsu::role_return_type<
			flattened_types,
			roles::texture
		>::type const &
	) const;

	parameters const
	size(
		typename majutsu::role_return_type<
			flattened_types,
			roles::size
		>::type const &
	) const;

	parameters const
	point_size(
		typename majutsu::role_return_type<
			flattened_types,
			roles::point_size
		>::type const &
	) const;

	parameters const
	texture_size() const;

	parameters const
	color(
		typename majutsu::role_return_type<
			flattened_types,
			roles::color
		>::type const &
	) const;

	parameters const
	default_color() const;

	parameters const
	depth(
		typename majutsu::role_return_type<
			flattened_types,
			roles::depth
		>::type const &
	) const;

	parameters const
	visible(
		typename majutsu::role_return_type<
			flattened_types,
			roles::visible
		>::type const &
	) const;

	parameters const
	rotation(
		typename majutsu::role_return_type<
			flattened_types,
			roles::rotation
		>::type const &
	) const;

	parameters const
	no_rotation_point() const;

	parameters const
	rotation_point(
		typename majutsu::role_return_type<
			flattened_types,
			roles::rotate_around
		>::type const &
	) const;

	parameters const
	repetition(
		typename majutsu::role_return_type<
			flattened_types,
			roles::repetition
		>::type const &
	) const;

	parameters const
	order(
		typename majutsu::role_return_type<
			flattened_types,
			roles::order
		>::type const &
	) const;

	parameters const
	adder(
		typename majutsu::role_return_type<
			flattened_types,
			roles::adder
		>::type const &
	) const;

	parameters const
	system(
		typename sprite::system<
			Choices
		>::type *
	) const;

	template<
		typename Role
	>
	parameters const
	set(
		typename majutsu::role_return_type<
			flattened_types,
			Role
		>::type const &
	) const;

	elements_type const &
	elements() const;
private:
	elements_type elements_;
};

}
}

#endif
