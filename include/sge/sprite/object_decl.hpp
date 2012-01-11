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


#ifndef SGE_SPRITE_OBJECT_DECL_HPP_INCLUDED
#define SGE_SPRITE_OBJECT_DECL_HPP_INCLUDED

#include <sge/sprite/color.hpp>
#include <sge/sprite/depth.hpp>
#include <sge/sprite/dim.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/parameters_fwd.hpp>
#include <sge/sprite/point_size.hpp>
#include <sge/sprite/repetition.hpp>
#include <sge/sprite/rotation.hpp>
#include <sge/sprite/rotation_center.hpp>
#include <sge/sprite/texture.hpp>
#include <sge/sprite/texture_coordinates.hpp>
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/texture_point_pos.hpp>
#include <sge/sprite/texture_point_size.hpp>
#include <sge/sprite/vector.hpp>
#include <sge/sprite/detail/make_class.hpp>
#include <sge/sprite/detail/object_base.hpp>
#include <sge/sprite/intrusive/connection_base_fwd.hpp>
#include <majutsu/role_return_type.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
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
		sge::sprite::detail::object_base<
			Choices
		>::type
{
	typedef typename sge::sprite::detail::make_class<
		Choices,
		boost::mpl::vector0<>
	>::type element_type;

	typedef typename element_type::memory_type::types flattened_types;
public:
	typedef Choices choices;

	typedef typename Choices::type_choices type_choices;

	typedef typename type_choices::unit_type unit;

	typedef typename type_choices::float_type float_type;

	typedef typename sge::sprite::depth<
		choices
	>::type depth_type;

	typedef typename sge::sprite::rotation<
		choices
	>::type rotation_type;

	typedef typename sge::sprite::rotation_center<
		choices
	>::type rotation_center_type;

	typedef typename sge::sprite::repetition<
		choices
	>::type repetition_type;

	typedef typename sge::sprite::texture_coordinates<
		choices
	>::type texture_coordinates_type;

	typedef typename sge::sprite::vector<
		choices
	>::type vector;

	typedef typename sge::sprite::dim<
		choices
	>::type dim;

	typedef typename sge::sprite::point_size<
		choices
	>::type point_size_type;

	typedef typename sge::sprite::texture_point_pos<
		choices
	>::type texture_point_pos_type;

	typedef typename sge::sprite::texture_point_size<
		choices
	>::type texture_point_size_type;

	typedef typename sge::sprite::color<
		choices
	>::type color_type;

	typedef typename sge::sprite::texture<
		choices
	>::type texture_type;

	typedef sge::sprite::parameters<
		choices
	> parameters_type;

	typedef sge::sprite::intrusive::connection_base<
		choices
	> connection_base;

	explicit
	object(
		element_type const &
	);

	explicit
	object(
		parameters_type const &
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

	texture_point_pos_type
	texture_point_pos() const;

	template<
		sge::sprite::texture_level
	>
	texture_point_pos_type
	texture_point_pos_level() const;

	texture_point_size_type
	texture_point_size() const;

	template<
		sge::sprite::texture_level
	>
	texture_point_size_type
	texture_point_size_level() const;

	depth_type
	z() const;

	bool
	visible() const;

	rotation_type
	rotation() const;

	rotation_center_type const
	rotation_center() const;

	repetition_type
	repetition() const;

	texture_coordinates_type const
	texture_coordinates() const;

	template<
		sge::sprite::texture_level
	>
	texture_coordinates_type const
	texture_coordinates_level() const;

	color_type const
	color() const;

	texture_type const
	texture() const;

	template<
		sge::sprite::texture_level
	>
	texture_type const
	texture_level() const;

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
	texture_point_pos(
		texture_point_pos_type
	);

	template<
		sge::sprite::texture_level
	>
	void
	texture_point_pos_level(
		texture_point_pos_type
	);

	void
	texture_point_size(
		texture_point_size_type
	);

	template<
		sge::sprite::texture_level
	>
	void
	texture_point_size_level(
		texture_point_size_type
	);

	void
	visible(
		bool
	);

	void
	texture(
		texture_type
	);

	template<
		sge::sprite::texture_level
	>
	void
	texture_level(
		texture_type
	);

	void
	rotation(
		rotation_type
	);

	void
	rotate_around(
		rotation_center_type const &
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
	transfer(
		typename majutsu::role_return_type<
			flattened_types,
			sge::sprite::roles::connection
		>::type const &
	);

	void
	transfer(
		connection_base &
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
