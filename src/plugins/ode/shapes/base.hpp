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

#ifndef SGE_ODE_SHAPES_BASE_HPP_INCLUDED
#define SGE_ODE_SHAPES_BASE_HPP_INCLUDED

#include "base_fwd.hpp"
#include "../group_fwd.hpp"
#include <sge/collision/shapes/base.hpp>
#include <ode/ode.h>

namespace sge
{
namespace ode
{
namespace shapes
{
class base
{
public:
	base(
		dGeomID);
	void assign_body(
		dBodyID);
	void add_to_group(
		group const &);
	~base();
protected:
	dGeomID shape_;
};
}
}
}

#endif