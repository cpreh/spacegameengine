#ifndef SGE_BSP_TREE_HPP_INCLUDED
#define SGE_BSP_TREE_HPP_INCLUDED

#include "../math/rect.hpp"

namespace sge
{

template<typename Size> class bsp_tree {
public:
	typedef Size size_type;
	typedef dim<size_type> dim_type;
	typedef basic_rect<size_type> value_type;
	typedef const value_type& const_reference;

	class iterator {
	public:
		iterator(node& ref)
			: ref(ref) {}
		const_reference operator*() const { return ref.rect; }
	private:
		node& ref;
	};

	bsp_tree(const size_type w, const size_type h)
		: head(value_type(0,0,w,h), 0)
	{}

	iterator insert(const dim_type dim)
	{
		return insert_recursive(dim, head);
	}

	void erase(const_iterator it)
	{
		delete &(it.ref);
	}

	iterator find(const value_type& t)
	{
		return find_recursive(t, head);
	}

	iterator end() { return iterator(node(head.rect)); }
private:
	struct node {
		node(const value_type& rect, const node* parent, node* const left = 0, node* const right = 0)
			: rect(rect), parent(parent), left(left), right(right)
		{}

		~node()
		{
			if(parent)
			{
				if(parent->left == this)
					parent->left = 0;
				else
					parent->right = 0;
			}
			delete left;
			delete right;
		}

		value_type rect;
		node* parent;
		node* left;
		node* right;
	};

	node head;

	iterator insert_recursive(const dim_type dim, node& n)
	{
		// case 1: left and right are absent
		if(!n.left && !n.right)
			return insert_node(n, n.left, dim);

		// case 2: right node is absent
		if(!n.right)
			return insert_case_2(dim, n, n.left, &n.right);

		// case 2: symmetric case
		if(!n.left)
			return insert_case_2(dim, n, n.right, &n.left);

		// case 3: both nodes are there
	}

	iterator insert_case_2(const dim_type dim, node& ref, node& exist, node*& empty)
	{
		if(exist.rect > dim)
		{
			iterator it = find_recursive(dim, exist);
			if(it != end())
				return it;
		}
		return insert_node(ref, empty, ref.rect - exist.rect);
	}

	iterator insert_node(node& ref, node*& n, const value_type& rect)
	{
		n = new node(rect, &ref);
		return iterator(*n);
	}

	iterator find_recursive(const value_type& t, node& n)
	{
		if(n.rect == t)
			return n;
		if(n.left && contains(n.left->rect, t))
			return find_recursive(t, *n.left);
		if(n.right && contains(n.right->rect, t))
			return find_recursive(t, *n.right);
		return end();
	}
};

}

#endif
