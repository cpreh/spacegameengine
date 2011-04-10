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
#include <sge/sprite/roles/texture_coordinates.hpp>
#include <sge/sprite/roles/visible.hpp>
#include <sge/image/color/any/object.hpp>
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
		// TODO: only add this when needed!
		boost::mpl::vector1<
			majutsu::role<
				majutsu::fundamental<
					bool
				>,
				detail::roles::use_center
			>
		>
	>::type elements_type;
public:
	typedef Choices choices;

	typedef typename elements_type::memory_type::types flattened_types;

	parameters();

	parameters &
	pos(
		typename majutsu::role_return_type<
			flattened_types,
			roles::pos
		>::type const &
	);

	parameters &
	center(
		typename majutsu::role_return_type<
			flattened_types,
			roles::pos
		>::type const &
	);

	parameters &
	texture(
		typename majutsu::role_return_type<
			flattened_types,
			roles::texture
		>::type const &
	);

	parameters &
	size(
		typename majutsu::role_return_type<
			flattened_types,
			roles::size
		>::type const &
	);

	parameters &
	point_size(
		typename majutsu::role_return_type<
			flattened_types,
			roles::point_size
		>::type const &
	);

	parameters &
	texture_size();

	parameters &
	color(
		typename majutsu::role_return_type<
			flattened_types,
			roles::color
		>::type const &
	);

	parameters &
	any_color(
		sge::image::color::any::object const &
	);

	parameters &
	default_color();

	parameters &
	depth(
		typename majutsu::role_return_type<
			flattened_types,
			roles::depth
		>::type const &
	);

	parameters &
	visible(
		typename majutsu::role_return_type<
			flattened_types,
			roles::visible
		>::type const &
	);

	parameters &
	rotation(
		typename majutsu::role_return_type<
			flattened_types,
			roles::rotation
		>::type const &
	);

	parameters &
	no_rotation_point();

	parameters &
	rotation_point(
		typename majutsu::role_return_type<
			flattened_types,
			roles::rotate_around
		>::type const &
	);

	parameters &
	repetition(
		typename majutsu::role_return_type<
			flattened_types,
			roles::repetition
		>::type const &
	);

	parameters &
	texture_coordinates(
		typename majutsu::role_return_type<
			flattened_types,
			roles::texture_coordinates
		>::type const &
	);

	parameters &
	order(
		typename majutsu::role_return_type<
			flattened_types,
			roles::order
		>::type const &
	);

	parameters &
	adder(
		typename majutsu::role_return_type<
			flattened_types,
			roles::adder
		>::type const &
	);

	parameters &
	system(
		typename sprite::system<
			Choices
		>::type *
	);

	template<
		typename Role
	>
	parameters &
	set(
		typename majutsu::role_return_type<
			flattened_types,
			Role
		>::type const &
	);

	elements_type const &
	elements() const;
private:
	elements_type elements_;
};

}
}

#endif
