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


#ifndef SGE_SPRITE_SYSTEM_HPP_INCLUDED
#define SGE_SPRITE_SYSTEM_HPP_INCLUDED

#include <sge/sprite/fwd.hpp>
#include <sge/sprite/system_base.hpp>
#include <sge/sprite/container.hpp>
#include <sge/export.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace sprite
{

class system : public system_base {
public:
	SGE_SYMBOL explicit system(
		renderer::device_ptr rend);
	
	typedef boost::function<
		void (
			object *,
			object *)
	> sort_method;

	typedef boost::function<
		bool (
			object const &,
			object const &)
	> equal_method;

	SGE_SYMBOL static sort_method const default_sort;
	SGE_SYMBOL static equal_method const default_equal;

	SGE_SYMBOL void render(
		container::iterator begin,
		container::iterator end,
		sort_method const &
			= default_sort,
		equal_method const &
			= default_equal);

	SGE_SYMBOL void render(
		object *begin,
		object *end,
		sort_method const &
			= default_sort,
		equal_method const &
			= default_equal);
	
	SGE_SYMBOL void render(
		object);
};

}
}

#endif
