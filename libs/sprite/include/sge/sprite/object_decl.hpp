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


namespace sge::sprite
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
	using
	element_type
	=
	sge::sprite::detail::make_class<
		Choices
	>;

	using
	all_types
	=
	typename
	element_type::all_types;

	using
	choices
	=
	Choices;

	using
	type_choices
	=
	typename
	Choices::type_choices;

	using
	unit
	=
	sge::sprite::types::basic::unit<
		type_choices
	>;

	using
	float_type
	=
	sge::sprite::types::basic::float_<
		type_choices
	>;

	using
	depth_type
	=
	sge::sprite::types::depth<
		type_choices
	>;

	using
	rotation_type
	=
	sge::sprite::types::rotation<
		type_choices
	>;

	using
	repetition_type
	=
	sge::sprite::types::repetition<
		type_choices
	>;

	using
	texture_coordinates_type
	=
	sge::sprite::types::texture_coordinates<
		type_choices
	>;

	using
	vector
	=
	sge::sprite::types::vector<
		type_choices
	>;

	using
	pos_type
	=
	sge::sprite::types::pos<
		type_choices
	>;

	using
	center_type
	=
	sge::sprite::types::center<
		type_choices
	>;

	using
	pos_or_center_type
	=
	sge::sprite::types::pos_or_center<
		type_choices
	>;

	using
	dim
	=
	sge::sprite::types::dim<
		type_choices
	>;

	using
	size_or_texture_size_type
	=
	sge::sprite::types::size_or_texture_size<
		type_choices
	>;

	using
	point_size_type
	=
	sge::sprite::types::point_size<
		type_choices
	>;

	using
	texture_point_pos_type
	=
	sge::sprite::types::texture_point_pos<
		type_choices
	>;

	using
	texture_point_size_type
	=
	sge::sprite::types::texture_point_size<
		type_choices
	>;

	using
	color_type
	=
	sge::sprite::color<
		choices
	>;

	using
	texture_type
	=
	sge::sprite::texture<
		choices
	>;

	using
	connection_type
	=
	sge::sprite::intrusive::connection<
		choices
	>;

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
	)
	noexcept;

	object &
	operator=(
		object const &
	);

	object &
	operator=(
		object &&
	)
	noexcept;

	~object();

	[[nodiscard]]
	unit
	x() const;

	[[nodiscard]]
	unit
	y() const;

	[[nodiscard]]
	vector
	pos() const;

	[[nodiscard]]
	vector
	center() const;

	[[nodiscard]]
	unit
	w() const;

	[[nodiscard]]
	unit
	h() const;

	[[nodiscard]]
	dim
	size() const;

	[[nodiscard]]
	point_size_type
	point_size() const;

	[[nodiscard]]
	texture_point_pos_type
	texture_point_pos() const;

	template<
		sge::sprite::texture_level
	>
	[[nodiscard]]
	texture_point_pos_type
	texture_point_pos_level() const;

	[[nodiscard]]
	texture_point_size_type
	texture_point_size() const;

	template<
		sge::sprite::texture_level
	>
	[[nodiscard]]
	texture_point_size_type
	texture_point_size_level() const;

	[[nodiscard]]
	depth_type
	z() const;

	[[nodiscard]]
	rotation_type
	rotation() const;

	[[nodiscard]]
	repetition_type
	repetition() const;

	[[nodiscard]]
	texture_coordinates_type
	texture_coordinates() const;

	template<
		sge::sprite::texture_level
	>
	[[nodiscard]]
	texture_coordinates_type
	texture_coordinates_level() const;

	[[nodiscard]]
	color_type
	color() const;

	[[nodiscard]]
	texture_type
	texture() const;

	template<
		sge::sprite::texture_level
	>
	[[nodiscard]]
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
	[[nodiscard]]
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

#endif
