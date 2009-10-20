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


#ifndef SGE_SPRITE_BASIC_DECL_HPP_INCLUDED
#define SGE_SPRITE_BASIC_DECL_HPP_INCLUDED

#include <sge/sprite/basic_fwd.hpp>
#include <sge/sprite/parameters_fwd.hpp>
#include <sge/sprite/detail/base.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <sge/math/dim/static.hpp>
#include <sge/math/dim/basic_decl.hpp>

namespace sge
{
namespace sprite
{

template<
	typename CoordType,
	typename Policies
>
class basic
:
	public detail::base<
		Policies
	>
{
public:
	typedef CoordType unit;

	typedef unit depth_type; // TODO

	typedef sge::math::dim::static_<
		CoordType,
		2
	>::type dim_type;

	typedef sprite::parameters<
		Policies
	> parameters;

	explicit basic(
		parameters const &
	);

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
	center(
		point const &
	);

	void
	dim(
		dim_type const &
	);

	unit
	x() const;

	unit
	y() const;

	depth_type
	z() const;

	point const
	pos() const;

	point const
	center() const;

	dim_type const
	dim() const;

	rect_type const
	rect() const;
private:
	point pos_;

	dim size_;

	depth_type z_;
};

}
}

#endif
