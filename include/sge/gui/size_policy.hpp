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


#ifndef SGE_GUI_SIZE_POLICY_HPP_INCLUDED
#define SGE_GUI_SIZE_POLICY_HPP_INCLUDED

#include <sge/container/bitfield/basic_impl.hpp>
#include <sge/gui/export.hpp>
#include <cstddef>

namespace sge
{
namespace gui
{
namespace axis_policy
{
enum internal_type
{
	none,
	can_grow,
	can_shrink,
	should_grow,
	size
};

typedef container::bitfield::basic<
	internal_type,
	size
> type;
}

class size_policy
{
	public:
	SGE_GUI_SYMBOL size_policy(
		axis_policy::type const &x,
		axis_policy::type const &y);
	SGE_GUI_SYMBOL axis_policy::type const &x() const;
	SGE_GUI_SYMBOL axis_policy::type const &y() const;
	// this is a hack so we can use it with the layouts::row::master stuff
	SGE_GUI_SYMBOL axis_policy::type const &index(std::size_t const i) const;
	SGE_GUI_SYMBOL static size_policy const default_policy;
	private:
	axis_policy::type x_,y_;
};
}
}

#endif
