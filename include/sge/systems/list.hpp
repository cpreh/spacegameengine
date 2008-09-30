/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SYSTEMS_LIST_HPP_INCLUDED
#define SGE_SYSTEMS_LIST_HPP_INCLUDED

#include "any.hpp"
#include <set>

namespace sge
{
namespace systems
{

class list {
public:
	explicit list(
		any const &);
	
	list const operator()(
		any const &) const;
private:
	typedef std::set<
		any
	> any_set;

	any_set states;
};

}
}

#endif
