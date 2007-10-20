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


#include "../resource.hpp"
#include "../renderer.hpp"

sge::d3d9::resource::resource(renderer* const r, const bool needs_restore)
: my_list(needs_restore ? &(r->resources) : 0),
  my_place(needs_restore ? my_list->insert(my_list->end(),this) : my_list->end())
{}

sge::d3d9::resource::~resource()
{
	if(my_list)
		my_list->erase(my_place);
}
