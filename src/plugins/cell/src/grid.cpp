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
#include "../grid.hpp"
#include "../grid_entry.hpp"
#include "../circle.hpp"
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/arithmetic.hpp>
#include <sge/math/dim/structure_cast.hpp>
#include <sge/container/field_impl.hpp>

sge::cell::grid::grid(
	collision::rect const &rect_)
:
	rect_(rect_),
	field_(
		field_type::dim_type(
			static_cast<field_type::size_type>(rect_.w() / 50),
			static_cast<field_type::size_type>(rect_.h() / 50)
		)
	)
{}

sge::cell::grid::~grid()
{}

sge::cell::field_type &
sge::cell::grid::field()
{
	return field_;
}

sge::cell::grid::pos_type const
sge::cell::grid::pos() const
{
	return rect_.pos();
}

sge::cell::grid::dim_type const
sge::cell::grid::cell_size() const
{
	return rect_.dim()
	/ math::dim::structure_cast<
		dim_type
	>(
		field_.dim()
	);
}
