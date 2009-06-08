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


#ifndef SGE_CELL_GRID_HPP_INCLUDED
#define SGE_CELL_GRID_HPP_INCLUDED

#include "field_type.hpp"
#include <sge/collision/rect.hpp>
#include <sge/container/field_decl.hpp>
#include <sge/math/vector/static.hpp>
#include <sge/math/dim/static.hpp>
#include <sge/math/rect/basic_decl.hpp>
#include <sge/time/funit.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace cell
{

class grid {
	SGE_NONCOPYABLE(grid)
public:
	explicit grid(
		collision::rect const &);
	
	~grid();

	field_type &field();

	typedef math::vector::static_<
		collision::unit,
		2
	>::type pos_type;

	typedef math::dim::static_<
		collision::unit,
		2
	>::type dim_type;

	pos_type const
	pos() const;

	collision::rect::dim_type const
	cell_size() const;
private:
	collision::rect const rect_;
	field_type field_;
};

}
}

#endif
