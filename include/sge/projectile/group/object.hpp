/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PROJECTILE_GROUP_OBJECT_HPP_INCLUDED
#define SGE_PROJECTILE_GROUP_OBJECT_HPP_INCLUDED

#include <sge/projectile/group/id.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace projectile
{
namespace group
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_PROJECTILE_SYMBOL explicit
	object(
		world &);

	SGE_PROJECTILE_SYMBOL 
	~object();
private:
	friend class sge::projectile::world;

	id category_,collides_;

	void
	collides_with(
		object const &);
};
}
}
}

#endif
