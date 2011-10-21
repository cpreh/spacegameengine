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


#ifndef SGE_SPRITE_OBJECT_DECL_HPP_INCLUDED
#define SGE_SPRITE_OBJECT_DECL_HPP_INCLUDED

#include <sge/sprite/color.hpp>
#include <sge/sprite/depth_type.hpp>
#include <sge/sprite/dim.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/point_size.hpp>
#include <sge/sprite/repetition_type.hpp>
#include <sge/sprite/rotation_type.hpp>
#include <sge/sprite/texture_coordinates.hpp>
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/vector.hpp>
#include <sge/sprite/detail/make_class.hpp>
#include <sge/sprite/intrusive/order.hpp>
#include <sge/sprite/intrusive/system_fwd.hpp>
#include <sge/sprite/intrusive/tag.hpp>
#include <sge/sprite/intrusive/detail/object_base_hook.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <majutsu/role_return_type.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{

template<
	typename Choices
>
class object
:
	public
		boost::mpl::if_<
			boost::mpl::contains<
				typename Choices::elements,
				intrusive::tag
			>,
			intrusive::detail::object_base_hook,
			boost::mpl::empty_base
		>::type
{
	typedef typename detail::make_class<
		Choices
	>::type element_type;

	typedef typename element_type::memory_type::types flattened_types;
public:
	typedef Choices choices;

	typedef typename Choices::elements elements;

	typedef typename Choices::type_choices type_choices;

	typedef typename type_choices::unit_type unit;

	typedef typename type_choices::float_type float_type;

	typedef typename sprite::depth_type<
		float_type
	>::type depth_type;

	typedef typename sprite::rotation_type<
		float_type
	>::type rotation_type;

	typedef typename sprite::repetition_type<
		float_type
	>::type repetition_type;

	typedef typename sprite::texture_coordinates<
		float_type
	>::type texture_coordinates_type;

	typedef typename sprite::vector<
		unit
	>::type vector;

	typedef typename sprite::dim<
		unit
	>::type dim;

	typedef typename sprite::point_size<
		unit
	>::type point_size_type;

	typedef typename type_choices::color_type color_format;

	typedef typename sprite::color<
		color_format
	>::type color_type;

	typedef intrusive::order order_type;

	typedef intrusive::system<
		Choices
	> system;

	object();

	explicit object(
		element_type const &
	);

	template<
		typename Parameters
	>
	explicit object(
		Parameters const &
	);

	object(
		object const &
	);

	object &
	operator=(
		object const &
	);

	~object();

	unit
	x() const;

	unit
	y() const;

	vector const
	pos() const;

	unit
	w() const;

	unit
	h() const;

	dim const
	size() const;

	point_size_type
	point_size() const;

	depth_type
	z() const;

	bool
	visible() const;

	rotation_type
	rotation() const;

	vector const
	rotation_center() const;

	repetition_type
	repetition() const;

	texture_coordinates_type const
	texture_coordinates() const;

	template<
		sprite::texture_level Level
	>
	texture_coordinates_type const
	texture_coordinates_level() const;

	color_type const
	color() const;

	texture::const_part_ptr const
	texture() const;

	template<
		sprite::texture_level Level
	>
	texture::const_part_ptr const
	texture_level() const;

	order_type
	order() const;

	void
	x(
		unit
	);

	void
	y(
		unit
	);

	void
	z(
		depth_type
	);

	void
	pos(
		vector const &
	);

	void
	w(
		unit
	);

	void
	h(
		unit
	);

	void
	size(
		dim const &
	);

	void
	point_size(
		point_size_type
	);

	void
	visible(
		bool
	);

	void
	texture(
		sge::texture::const_part_ptr
	);

	template<
		sprite::texture_level
	>
	void
	texture_level(
		sge::texture::const_part_ptr
	);

	void
	rotation(
		rotation_type
	);

	void
	rotate_around(
		vector const &
	);

	void
	reset_rotation();

	void
	repeat(
		repetition_type
	);

	void
	texture_coordinates(
		texture_coordinates_type const &
	);

	template<
		sprite::texture_level
	>
	void
	texture_coordinates_level(
		texture_coordinates_type const &
	);

	void
	color(
		color_type const &
	);

	void
	order(
		order_type
	);

	void
	transfer(
		system &
	);

	template<
		typename Role
	>
	typename majutsu::role_return_type<
		flattened_types,
		Role
	>::type
	get() const;

	template<
		typename Role
	>
	void
	set(
		typename majutsu::role_return_type<
			flattened_types,
			Role
		>::type const &
	);
private:
	element_type elements_;
};

}
}

#endif
