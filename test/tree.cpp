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


#include <sge/container/tree.hpp>
#include <sge/make_auto_ptr.hpp>
#include <string>
#include <iostream>
#include <ostream>
#include <iterator>

namespace
{

template<
	typename Tree
>
struct inorder_traversal {
	explicit inorder_traversal(
		Tree &tree_)
	:
		tree_(tree_)
	{}

	typedef typename Tree::iterator tree_iterator;

	struct iterator {
		explicit iterator(
			tree_iterator const &it)
		:
			it(it)
		{}

		iterator &operator++()
		{
			if(!it->empty())
				it = it->begin();
			else if(it->has_parent())
				it = it->child_position();	
			return *this;
		}
		
		typename std::iterator_traits<tree_iterator>::reference
		operator *() const
		{
			return *it;	
		}

		bool operator!=(
			iterator const &it) const
		{
			return *this != it;
		}
	private:
		tree_iterator it;
	};

	iterator begin()
	{
		return iterator(tree_.begin());
	}
	iterator end()
	{
		return iterator(tree_.end());
	}
private:
	Tree &tree_;
};

}

int main()
{
	typedef sge::container::tree<
		std::string
	> string_tree;

	string_tree tree("hello");

	{
		string_tree::auto_ptr child1(
			sge::make_auto_ptr<
				string_tree
			>("blubb"));
		
		tree.push_back(
			child1);
	}

	typedef 
	inorder_traversal<
		string_tree
	> inorder_trav;

	inorder_trav trav(
		tree);
	
	for(inorder_trav::iterator it = trav.begin(); it != trav.end(); ++it)
		std::cout << (*it).value() << '\n';
}
