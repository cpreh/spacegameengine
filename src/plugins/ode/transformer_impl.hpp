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


#ifndef SGE_ODE_TRANSFORMER_IMPL_HPP_INCLUDED
#define SGE_ODE_TRANSFORMER_IMPL_HPP_INCLUDED

#include <fcppt/math/inverse.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/math/null.hpp>
#include <algorithm>

namespace
{
sge::collision::unit calculate_scaling(
	sge::collision::optional_box const &_r)
{
	if (!_r)
		return
			static_cast<sge::collision::unit>(
				1);

	return
		static_cast<sge::collision::unit>(
			fcppt::math::inverse<sge::collision::unit>(
				std::max(
					_r->dimension().w(),
					_r->dimension().h())));
}
}


sge::ode::transformer::transformer(
	collision::optional_box const &_r)
:
	scaling_(
		calculate_scaling(
			_r)),
	inverse_scaling_(
		fcppt::math::inverse(
			scaling_)),
	translation_(
		_r
		?
			collision::point(
				-_r->pos().x(),
				-_r->pos().y(),
				fcppt::math::null<collision::unit>())
		:
			collision::point::null())
{
}

sge::collision::point const
sge::ode::transformer::position_from_ode(
	point const &_p) const
{
	return
		fcppt::math::vector::structure_cast<collision::point>(
			_p*
			static_cast<dReal>(
				inverse_scaling_)-
			fcppt::math::vector::structure_cast<point>(
				translation_));
}

sge::collision::point const
sge::ode::transformer::velocity_from_ode(
	point const &_p) const
{
	return
		fcppt::math::vector::structure_cast<collision::point>(
			_p*
			static_cast<dReal>(
				inverse_scaling_));
}

sge::collision::dim const
sge::ode::transformer::dim_from_ode(
	dim const &_d) const
{
	return
		fcppt::math::dim::structure_cast<collision::dim>(
			static_cast<dReal>(
				inverse_scaling_)*_d);
}

sge::ode::point const sge::ode::transformer::position_to_ode(
	collision::point const &_p) const
{
	return
		fcppt::math::vector::structure_cast<point>(
			(_p + translation_)*scaling_);
}

sge::ode::point const sge::ode::transformer::velocity_to_ode(
	collision::point const &_p) const
{
	return
		fcppt::math::vector::structure_cast<point>(
			_p*scaling_);
}

sge::ode::dim const sge::ode::transformer::dim_to_ode(
	sge::collision::dim const &_d) const
{
	return
		fcppt::math::dim::structure_cast<dim>(
			_d*scaling_);
}

sge::collision::unit sge::ode::transformer::unit_from_ode(
	dReal const _d) const
{
	return
		static_cast<collision::unit>(
			_d)*inverse_scaling_;
}

dReal sge::ode::transformer::unit_to_ode(
	collision::unit const _d) const
{
	return
		static_cast<dReal>(
			_d)*scaling_;
}

#endif
