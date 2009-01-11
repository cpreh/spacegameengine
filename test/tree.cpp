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
#include <stack>

namespace
{

template<
	typename Tree
>
struct traversal {
	explicit traversal(
		Tree &tree_)
	:
		tree_(tree_)
	{}

	typedef typename Tree::iterator tree_iterator;

	typedef std::stack<
		tree_iterator
	> stack_type;

	struct iterator {
		iterator(
			tree_iterator const &it,
			stack_type &positions)
		:
			it(it),
			positions(positions)
		{}

		iterator &operator++()
		{
			if(!it->empty())
			{
				positions.push(it);
				it = it->begin();
			}
			else
			{
				while(!positions.empty() && positions.top() != positions.top()->parent().end())
				{
					it = positions.top();
					positions.pop();
				}
				++it;
			}
			return *this;
		}
		
		typename std::iterator_traits<tree_iterator>::reference
		operator *() const
		{
			return *it;	
		}

		bool operator!=(
			iterator const &s) const
		{
			return s.it  != it;
		}
	private:
		tree_iterator it;
		stack_type &positions;
	};

	iterator begin()
	{
		return iterator(tree_.begin(), positions);
	}
	iterator end()
	{
		return iterator(tree_.end(), positions);
	}
private:
	Tree &tree_;

	stack_type positions;
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

	{
		string_tree::auto_ptr child2(
			sge::make_auto_ptr<
				string_tree
			>("blah"));
	
		tree.push_back(
			child2);
	}

	typedef 
	traversal<
		string_tree
	> traversal_type;

	traversal_type trav(
		tree);
	
	for(traversal_type::iterator it = trav.begin(); it != trav.end(); ++it)
		std::cout << (*it).value() << std::endl;
}
