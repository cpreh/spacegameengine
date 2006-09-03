#ifndef SGE_BSP_TREE_HPP_INCLUDED
#define SGE_BSP_TREE_HPP_INCLUDED

#include <stdexcept>
#include "../math/rect.hpp"
#include "../math/dim.hpp"
#include "../math/vector2.hpp"

namespace sge
{

template<typename Size> class bsp_tree {
public:
	typedef Size size_type;
	typedef vector2<size_type> point_type;
	typedef basic_dim<size_type> dim_type;
	typedef basic_rect<size_type> value_type;
	typedef const value_type& const_reference;
private:
	struct node {
		node(const value_type& rect, node* const parent, const bool final, node* const left = 0, node* const right = 0)
			: rect(rect), parent(parent), left(left), right(right), final(final)
		{}

		~node()
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
			delete right;
		}

		friend bool operator==(const node& l, const node& r)
		{
			return l.rect == r.rect;
		}
		friend bool operator!=(const node& l, const node& r)
		{
			return !(l == r);
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

	bsp_tree(const dim_type dim)
		: head(value_type(point_type(0,0),dim), 0, false)
	{}

	iterator insert(const dim_type dim)
	{
		return insert_recursive(dim, head);
	}

	void erase(iterator it)
	{
		delete it.ref;
	}

	iterator find(const value_type& t)
	{
		return find_recursive(t, head);
	}

	iterator end() { return iterator(0); }
private:
	node head;

	iterator insert_recursive(const dim_type dim, node& n)
	{
		if(n.final || dim > n.rect)
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

	iterator insert_case_2(const dim_type dim, node& ref, node& exist, node*& empty)
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
		if(dim.w > free_w && dim.h > free_h)
			return end();

		// case 2: left is the existing node so existing rect is at left-top
		if(ref.left == &exist)
		{
			// case 2.1: insert at bottom
			if(dim.h <= free_h)
				return insert_two(dim, ref, empty, value_type(rr.left, er.bottom+1, rr.right, rr.bottom));
			// case 2.2: insert at right
			else // if(dim.w <= free_w)
				return insert_two(dim, ref, empty, value_type(er.right+1, rr.top, rr.right, rr.bottom));
		}

		// case 3: right is the existing node so occupy the rest
		// case 3.1: existing node is at bottom
		if(er.bottom == rr.bottom)
			return insert_two(dim, ref, empty, value_type(rr.left, rr.top, rr.right, er.top+1));
		// case 3.2: existing node is at right
		else
			return insert_two(dim, ref, empty, value_type(rr.left, rr.top, er.left+1, rr.bottom));
	}

	iterator insert_node(node& ref, node*& n, const bool final, const value_type& rect)
	{
		n = new node(rect, &ref, final);
		return iterator(n);
	}

	iterator insert_two(const dim_type dim, node& ref, node*& n, const value_type& rect)
	{
		return insert_recursive(dim, *insert_node(ref, n, false, rect).ref);
	}

	iterator find_recursive(const value_type& t, node& n)
	{
		if(n.rect == t)
			return iterator(&n);
		if(n.left && contains(n.left->rect, t))
			return find_recursive(t, *n.left);
		if(n.right && contains(n.right->rect, t))
			return find_recursive(t, *n.right);
		return end();
	}
};

}

#endif
