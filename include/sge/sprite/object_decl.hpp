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


#ifndef SGE_SPRITE_OBJECT_DECL_HPP_INCLUDED
#define SGE_SPRITE_OBJECT_DECL_HPP_INCLUDED

#include <sge/sprite/detail/make_class.hpp>
#include <sge/sprite/intrusive/detail/object_base_hook.hpp>
#include <sge/sprite/intrusive/order.hpp>
#include <sge/sprite/intrusive/system_fwd.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/point.hpp>
#include <sge/sprite/dim.hpp>
#include <sge/sprite/depth_type.hpp>
#include <sge/sprite/rotation_type.hpp>
#include <sge/sprite/repetition_type.hpp>
#include <sge/sprite/color.hpp>
#include <sge/texture/part_fwd.hpp>
#include <majutsu/role_return_type.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/empty_base.hpp>

namespace sge
{
namespace sprite
{

template<
	typename Choices,
	typename Elements
>
class object
:
	public
		boost::mpl::if_<
			boost::mpl::contains<
				Elements,
				intrusive::tag	
			>,
			intrusive::detail::object_base_hook,
			boost::mpl::empty_base
		>::type
{
	typedef typename detail::make_class<
		Choices,
		Elements
	>::type element_type;

	typedef typename element_type::memory_type::types flattened_types;
public:
	typedef Choices choices;
	
	typedef Elements elements;

	typedef typename Choices::unit_type unit;

	typedef typename sprite::depth_type<
		Choices
	>::type depth_type;

	typedef typename sprite::rotation_type<
		Choices
	>::type rotation_type;

	typedef typename sprite::repetition_type<
		Choices
	>::type repetition_type;

	typedef typename sprite::point<
		Choices
	>::type point;

	typedef typename sprite::dim<
		Choices
	>::type dim;

	typedef typename sprite::color<
		Choices
	>::type color_type;

	typedef typename intrusive::order<
		Choices
	>::type order_type;

	typedef intrusive::system<
		Choices,
		Elements
	> system;

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

	unit
	x() const;

	unit
	y() const;

	point const
	pos() const;

	unit
	w() const;

	unit
	h() const;

	dim const
	size() const;

	depth_type
	z() const;

	bool
	visible() const;

	rotation_type
	rotation() const;

	point const
	rotation_center() const;

	repetition_type
	repeat() const;

	color_type const
	color() const;

	texture::const_part_ptr const
	texture() const;

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
		point const &
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
	visible(
		bool
	);

	void
	texture(
		sge::texture::const_part_ptr
	);

	void 
	rotation(
		rotation_type
	);

	void
	rotate_around(
		point const &
	);

	void
	reset_rotation();

	void
	repeat(
		repetition_type
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
