/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_BSP_TREE_HPP_INCLUDED
#define SGE_BSP_TREE_HPP_INCLUDED

#include <cstddef>
#include "../math/rect.hpp"
#include "../math/dim.hpp"
#include "../math/vector.hpp"

namespace sge
{

class bsp_tree {
public:
	typedef std::size_t size_type;
	typedef math::vector<size_type,2> point_type;
	typedef math::dim<size_type,2> dim_type;
	typedef basic_rect<size_type> value_type;
	typedef const value_type& const_reference;
private:
	struct node {
		node(const value_type& rect, node* const parent, const bool final, node* const left = 0, node* const right = 0);
		~node();

		friend bool operator==(const node& l, const node& r)
		{
			return l.rect == r.rect;
		}
		friend bool operator!=(const node& l, const node& r)
		{
			return !(l==r);
		}

		value_type rect;
		node* parent;
		node* left;
		node* right;
		bool final;
	};
public:
	class iterator {
		friend class bsp_tree;
		iterator(node* ref)
			: ref(ref) {}
	public:
		const_reference operator*() const { return ref->rect; }

		friend bool operator== (const iterator& l, const iterator& r)
		{
			return l.ref == r.ref;
		}
		friend bool operator!= (const iterator& l, const iterator& r)
		{
			return !(l==r);
		}
	private:
		node* ref;
	};

	bsp_tree(const dim_type dim);

	iterator insert(const dim_type dim);
	void erase(iterator it);
	iterator find(const value_type& t);
	iterator end();
private:
	node head;

	iterator insert_recursive(const dim_type dim, node& n);
	iterator insert_case_2(const dim_type dim, node& ref, node& exist, node*& empty);
	iterator insert_node(node& ref, node*& n, const bool final, const value_type& rect);
	iterator insert_two(const dim_type dim, node& ref, node*& n, const value_type& rect);
	iterator find_recursive(const value_type& t, node& n);
};

}

#endif
