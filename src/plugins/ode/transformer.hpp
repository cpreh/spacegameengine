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

#ifndef SGE_ODE_TRANSFORMER_HPP_INCLUDED
#define SGE_ODE_TRANSFORMER_HPP_INCLUDED

#include "point.hpp"
#include "dim.hpp"
#include <sge/collision/optional_rect.hpp>
#include <sge/collision/point.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <sge/collision/dim.hpp>

namespace sge
{
namespace ode
{
class transformer
{
public:
	inline transformer(
		sge::collision::optional_rect const &);
	collision::point const
	inline position_from_ode(
		point const &) const;
	inline collision::point const
	velocity_from_ode(
		point const &) const;
	inline collision::dim const
	dim_from_ode(
		dim const &) const;
	inline point const
	position_to_ode(
		collision::point const &) const;
	inline point const
	velocity_to_ode(
		collision::point const &) const;
	inline dim const
	dim_to_ode(
		collision::dim const &) const;
	inline collision::unit
	unit_from_ode(
		dReal) const;
	inline dReal
	unit_to_ode(
		collision::unit) const;
private:
	sge::collision::unit
		scaling_,
		inverse_scaling_;
	sge::collision::point
		translation_;
};
}
}

#endif
