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


#include "../bsp_tree.hpp"

sge::bsp_tree::node::node(const value_type& rect, node* const parent, const bool final, node* const left, node* const right)
 : rect(rect), parent(parent), left(left), right(right), final(final)
{}

sge::bsp_tree::node::~node()
{
	if(parent)
	{
		if(parent->left == this)
			parent->left = 0;
		else
			parent->right = 0;
		if(parent->left == 0 && parent->right == 0 && parent->parent != 0)
			delete parent;
	}
	delete left;
	left = 0;
	delete right;
	right = 0;
}
