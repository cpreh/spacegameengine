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
#include <sge/container/traversal.hpp>
#include <sge/make_auto_ptr.hpp>
#include <string>
#include <iostream>
#include <ostream>

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

	tree.push_back(
		"foobar");

	typedef 
	sge::container::traversal<
		string_tree const
	> traversal_type;

	traversal_type const trav(
		tree);
	
	for(traversal_type::iterator it = trav.begin(); it != trav.end(); ++it)
		std::cout << (*it).value() << std::endl;
}
