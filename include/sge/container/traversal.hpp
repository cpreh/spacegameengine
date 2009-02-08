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


#ifndef SGE_CONTAINER_TRAVERSAL_HPP_INCLUDED
#define SGE_CONTAINER_TRAVERSAL_HPP_INCLUDED

#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <stack>

namespace sge
{
namespace container
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

	struct iterator;
private:
	typedef typename boost::mpl::if_<
		boost::is_const<
			Tree
		>,
		typename Tree::const_iterator,
		typename Tree::iterator
	>::type tree_iterator;

	typedef std::stack<
		tree_iterator
	> stack_type;

	typedef boost::iterator_facade<
		iterator,
		typename tree_iterator::value_type,
		boost::bidirectional_traversal_tag,
		typename tree_iterator::reference
	> iterator_base;
public:
	struct iterator : iterator_base {
		explicit iterator(
			tree_iterator const &it)
		:
			it(it)
		{}

		typedef typename iterator_base::value_type value_type;
		typedef typename iterator_base::reference reference;
		typedef typename iterator_base::pointer pointer;
		typedef typename iterator_base::difference_type difference_type;
		typedef typename iterator_base::iterator_category iterator_category;

		tree_iterator const
		internal() const
		{
			return it;
		}

		friend class boost::iterator_core_access;
	private:
		void increment()
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
		}

		void decrement()
		{
			// TODO:
		}
		
		reference dereference() const
		{
			return *it;
		}

		bool equal(
			iterator const &s) const
		{
			return s.it  == it;
		}

		tree_iterator it;
		stack_type positions;
	};

	iterator const begin() const
	{
		return iterator(tree_.begin());
	}
	iterator const end() const
	{
		return iterator(tree_.end());
	}
private:
	Tree &tree_;
};

}
}

#endif
