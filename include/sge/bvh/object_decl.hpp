/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_BVH_OBJECT_DECL_HPP_INCLUDED
#define SGE_BVH_OBJECT_DECL_HPP_INCLUDED

#include <sge/bvh/tree_traits.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace bvh
{
template<typename Traits>
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	typedef
	Traits
	traits;

	typedef
	typename
	traits::leaf_sequence
	leaf_sequence;

	typedef
	typename
	traits::tree_representation
	tree_representation;

	object();

	void
	insert(
		leaf_sequence const &);

	tree_representation const &
	representation() const;

	~object();
private:
	leaf_sequence leaves_;
	tree_representation representation_;
};
}
}

#endif
