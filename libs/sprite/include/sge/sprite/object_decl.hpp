//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_OBJECT_DECL_HPP_INCLUDED
#define SGE_SPRITE_OBJECT_DECL_HPP_INCLUDED

#include <sge/sprite/color_fwd.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/texture.hpp>
#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/detail/make_class.hpp>
#include <sge/sprite/detail/object_base.hpp>
#include <sge/sprite/intrusive/connection_fwd.hpp>
#include <sge/sprite/types/center_fwd.hpp>
#include <sge/sprite/types/depth.hpp>
#include <sge/sprite/types/dim_fwd.hpp>
#include <sge/sprite/types/point_size.hpp>
#include <sge/sprite/types/pos_fwd.hpp>
#include <sge/sprite/types/pos_or_center.hpp>
#include <sge/sprite/types/repetition_fwd.hpp>
#include <sge/sprite/types/rotation.hpp>
#include <sge/sprite/types/size_or_texture_size.hpp>
#include <sge/sprite/types/texture_coordinates_fwd.hpp>
#include <sge/sprite/types/texture_point_pos_fwd.hpp>
#include <sge/sprite/types/texture_point_size.hpp>
#include <sge/sprite/types/vector_fwd.hpp>
#include <sge/sprite/types/basic/dim_decl.hpp>
#include <sge/sprite/types/basic/float.hpp>
#include <sge/sprite/types/basic/homogenous_pair_decl.hpp>
#include <sge/sprite/types/basic/unit.hpp>
#include <sge/sprite/types/basic/vector_decl.hpp>
#include <fcppt/record/enable_vararg_ctor.hpp>
#include <fcppt/record/label_value_type.hpp>


namespace sge
{
namespace sprite
{

template<
	typename Choices
>
class object final
:
	public
		sge::sprite::detail::object_base<
			Choices
		>
{
public:
	typedef
	sge::sprite::detail::make_class<
		Choices
	>
	element_type;

	typedef
	typename
	element_type::all_types
	all_types;

	typedef
	Choices
	choices;

	typedef
	typename
	Choices::type_choices
	type_choices;

	typedef
	sge::sprite::types::basic::unit<
		type_choices
	>
	unit;

	typedef
	sge::sprite::types::basic::float_<
		type_choices
	>
	float_type;

	typedef
	sge::sprite::types::depth<
		type_choices
	>
	depth_type;

	typedef
	sge::sprite::types::rotation<
		type_choices
	>
	rotation_type;

	typedef
	sge::sprite::types::repetition<
		type_choices
	>
	repetition_type;

	typedef
	sge::sprite::types::texture_coordinates<
		type_choices
	>
	texture_coordinates_type;

	typedef
	sge::sprite::types::vector<
		type_choices
	>
	vector;

	typedef
	sge::sprite::types::pos<
		type_choices
	>
	pos_type;

	typedef
	sge::sprite::types::center<
		type_choices
	>
	center_type;

	typedef
	sge::sprite::types::pos_or_center<
		type_choices
	>
	pos_or_center_type;

	typedef
	sge::sprite::types::dim<
		type_choices
	>
	dim;

	typedef
	sge::sprite::types::size_or_texture_size<
		type_choices
	>
	size_or_texture_size_type;

	typedef
	sge::sprite::types::point_size<
		type_choices
	>
	point_size_type;

	typedef
	sge::sprite::types::texture_point_pos<
		type_choices
	>
	texture_point_pos_type;

	typedef
	sge::sprite::types::texture_point_size<
		type_choices
	>
	texture_point_size_type;

	typedef
	sge::sprite::color<
		choices
	>
	color_type;

	typedef
	sge::sprite::texture<
		choices
	>
	texture_type;

	typedef
	sge::sprite::intrusive::connection<
		choices
	>
	connection_type;

	template<
		typename... Args,
		typename =
			fcppt::record::enable_vararg_ctor<
				Args...
			>
	>
	explicit
	object(
		Args &&...
	);

	object(
		object const &
	);

	object(
		object &&
	);

	object &
	operator=(
		object const &
	);

	object &
	operator=(
		object &&
	);

	~object();

	unit
	x() const;

	unit
	y() const;

	vector
	pos() const;

	vector
	center() const;

	unit
	w() const;

	unit
	h() const;

	dim
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

	rotation_type
	rotation() const;

	repetition_type
	repetition() const;

	texture_coordinates_type
	texture_coordinates() const;

	template<
		sge::sprite::texture_level
	>
	texture_coordinates_type
	texture_coordinates_level() const;

	color_type
	color() const;

	texture_type
	texture() const;

	template<
		sge::sprite::texture_level
	>
	texture_type const &
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
		vector
	);

	void
	center(
		vector
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
		dim
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

	template<
		typename Role
	>
	fcppt::record::label_value_type<
		element_type,
		Role
	> const &
	get() const;

	template<
		typename Role
	>
	void
	set(
		fcppt::record::label_value_type<
			element_type,
			Role
		> const &
	);
private:
	element_type elements_;
};

}
}

#endif
