/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RESOURCE_TREE_PATH_WITH_RESOURCE_DECL_HPP_INCLUDED
#define SGE_RESOURCE_TREE_PATH_WITH_RESOURCE_DECL_HPP_INCLUDED

#include <sge/resource_tree/path.hpp>
#include <sge/resource_tree/path_with_resource_fwd.hpp>


namespace sge
{
namespace resource_tree
{
/**
\brief Represents a pair of a path and a resource
*/
template<typename T>
class path_with_resource
{
public:
	path_with_resource(
		sge::resource_tree::path const &,
		T);

	sge::resource_tree::path const &
	path() const;

	T const
	resource() const;
private:
	sge::resource_tree::path path_;
	T resource_;
};
}
}

#endif
