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


#include "../rect_bsp_tree.hpp"

sge::rect_bsp_tree::node::node(const value_type& rect, node* const parent, const bool final, node* const left, node* const right)
 : rect(rect), parent(parent), left(left), right(right), final(final)
{}

sge::rect_bsp_tree::node::~node()
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

bool sge::rect_bsp_tree::node::operator==(const node& r) const
{
	return rect == r.rect;
}

bool sge::rect_bsp_tree::node::operator!=(const node& r) const
{
	return !(*this==r);
}


sge::rect_bsp_tree::iterator::iterator(node* const ref)
: ref(ref)
{}

sge::rect_bsp_tree::const_reference sge::rect_bsp_tree::iterator::operator*() const 
{
	return ref->rect;
}

bool sge::rect_bsp_tree::iterator::operator==(const iterator& r) const
{
	return ref == r.ref;
}

bool sge::rect_bsp_tree::iterator::operator!=(const iterator& r) const
{
	return !(*this==r);
}


sge::rect_bsp_tree::rect_bsp_tree(const dim_type dim)
 : head(value_type(point_type(0,0),dim), 0, false)
{}

sge::rect_bsp_tree::iterator sge::rect_bsp_tree::insert(const dim_type dim)
{
	return insert_recursive(dim, head);
}

void sge::rect_bsp_tree::erase(const iterator it)
{
	delete it.ref;
}

sge::rect_bsp_tree::iterator sge::rect_bsp_tree::find(const value_type& t)
{
	return find_recursive(t, head);
}

sge::rect_bsp_tree::iterator sge::rect_bsp_tree::end()
{
	return iterator(0);
}

sge::rect_bsp_tree::iterator sge::rect_bsp_tree::insert_recursive(const dim_type dim, node& n)
{
	if(n.final || dim.w() > n.rect.width() || dim.h() > n.rect.height())
		return end();

	// case 1: left and right are absent -> always put in the left node
	if(!n.left && !n.right)
		return insert_node(n, n.left, true, value_type(point_type(n.rect.left, n.rect.top), dim));
		
	// case 2: right node is absent but left node is there
	if(n.left && !n.right)
		return insert_case_2(dim, n, *n.left, n.right);

	// case 2: symmetric case (left node is absent but right node is there)
	if(n.right && !n.left)
		return insert_case_2(dim, n, *n.right, n.left);

	// case 3: both nodes are there
	iterator ret = insert_recursive(dim, *n.left);
	if(ret == end())
		ret = insert_recursive(dim, *n.right);
	return ret;
}

sge::rect_bsp_tree::iterator sge::rect_bsp_tree::insert_case_2(const dim_type dim, node& ref, node& exist, node*& empty)
{
	// first look if we can put the new rect in somewhere down the existing node
	iterator ret = insert_recursive(dim, exist);
	if(ret != end())
		return ret;

	const size_type free_w = width(ref.rect) - width(exist.rect),
	                free_h = height(ref.rect) - height(exist.rect);

	const value_type& rr = ref.rect,
	                  er = exist.rect;
	// case 1: width and height are too big
	if(dim.w() > free_w && dim.h() > free_h)
		return end();

	// case 2: left is the existing node so existing rect is at left-top
	if(ref.left == &exist)
	{
		// case 2.1: insert at bottom
		if(dim.h() <= free_h)
			return insert_two(dim, ref, empty, value_type(rr.left, er.bottom, rr.right, rr.bottom));
		// case 2.2: insert at right
		else // if(dim.w <= free_w)
			return insert_two(dim, ref, empty, value_type(er.right, rr.top, rr.right, rr.bottom));
	}

	// case 3: right is the existing node so occupy the rest
	// case 3.1: existing node is at bottom
	if(er.bottom == rr.bottom)
		return insert_two(dim, ref, empty, value_type(rr.left, rr.top, rr.right, er.top));
	// case 3.2: existing node is at right
	else
		return insert_two(dim, ref, empty, value_type(rr.left, rr.top, er.left, rr.bottom));
}

sge::rect_bsp_tree::iterator sge::rect_bsp_tree::insert_node(node& ref, node*& n, const bool final, const value_type& rect)
{
	n = new node(rect, &ref, final);
	return iterator(n);
}

sge::rect_bsp_tree::iterator sge::rect_bsp_tree::insert_two(const dim_type dim, node& ref, node*& n, const value_type& rect)
{
	return insert_recursive(dim, *insert_node(ref, n, false, rect).ref);
}

sge::rect_bsp_tree::iterator sge::rect_bsp_tree::find_recursive(const value_type& t, node& n)
{
	if(n.rect == t)
		return iterator(&n);
	if(n.left && contains(n.left->rect, t))
		return find_recursive(t, *n.left);
	if(n.right && contains(n.right->rect, t))
		return find_recursive(t, *n.right);
	return end();
}
