/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2007  Simon Stienen (s.stienen@slashlife.org)

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

#ifndef SGE_TREE_HPP_INCLUDED
#define SGE_TREE_HPP_INCLUDED

#include <iterator>
#include <memory>

namespace sge {

template<typename T_, typename Alloc_ = std::allocator<T_> > class tree {
public:
	typedef T_                                       value_type;
	typedef Alloc_                                   allocator_type;
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::size_type       depth_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::reference       reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;

private:
	struct node {
		typedef typename allocator_type::template rebind<node>::other allocator_type;

		static node *alloc() {
			allocator_type a;
			node *n = a.allocate(1);
			a.construct(n, node());
			return n;
		}
		static void dealloc(node *n) {
			allocator_type a;
			a.destroy(n);
			a.deallocate(n, 1);
		}

		value_type value;
		node *parent;
		node *prev,  *next; // siblings
		node *first, *last; // children
		size_type size;

		node() : parent(0), prev(0), next(0), first(0), last(0), size(0) {}
		node(const node &) : parent(0), prev(0), next(0), first(0), last(0), size(0) {}
		~node() { clear(); unlink(); }

		void clear() {
			while (first)
				dealloc(first);
		}

		node *clone() {
			node *node_=0, *child_=0, *current_=first;
			try {
				node_ = alloc();
				node_->value = value;
				while (current_) {
					child_ = current_->clone();
					node_->link_child(child_);
					current_ = current_->next;
				}
			} catch(...) {
				dealloc(child_);
				dealloc(node_);
				throw;
			}
			return node_;
		}

		void swap(node *other) {
			if (other == this) return;
			{
				node *tmp = other->first;
				other->first = first;
				first = tmp;
				tmp = other->last;
				other->last = last;
				last = tmp;
			}
			{
				size_type tmp = other->size;
				other->size = size;
				size = tmp;
			}
			value.swap(other->value);
			for (node *b=other->first; b; b=b->next)
				b->parent = other;
			for (node *b=first; b; b=b->next)
				b->parent = this;
		}

		void link_sibling(node *newchild) {
			// inserts as previous sibling
			newchild->unlink();

			newchild->parent = parent;

			if (prev) {
				newchild->prev = prev;
				prev->next = newchild;
			}
			// else: newchild->prev has alreade be 0ed by unlink()

			prev = newchild;
			newchild->next = this;

			if (parent) {
				++(parent->size);
				if (parent->first == this)
					parent->first = newchild;
			}
		}

		void link_child(node *newchild) {
			// inserts as last child
			newchild->unlink();

			++size;
			newchild->parent = this;
			newchild->prev   = last;
			if (last)
				last->next   = newchild;
			else
				first = newchild;
			last             = newchild;
		}

		void unlink() {
			if (next) next->prev = prev;
			if (prev) prev->next = next;
			if (parent) {
				--parent->size;
				if (parent->first == this)
					parent->first = next;
				if (parent->last  == this)
					parent->last  = prev;
				parent = 0;
			}
			next = prev = 0;
		}
	};

	typedef typename node::allocator_type node_allocator_type;
	node_allocator_type keep_alive_dummy;

	node root_;

public:
	template<bool Const_, bool Reverse_, bool Tree_> struct iterator_base {};

	template<bool Const_, bool Reverse_, bool Tree_> struct iterator_common_base {
		typedef typename iterator_base<Const_, Reverse_, Tree_>::type self_t;
		typedef typename iterator_base<Const_, false,    false>::type base_t;

		template<typename T> struct impl_const_if_const {
			template<bool, typename U> struct implementation;
			template<typename U> struct implementation<false, U> { typedef U type; };
			template<typename U> struct implementation<true , U> { typedef const U type; };
			typedef typename implementation<Const_, T>::type type;
		};

		typedef typename tree<T_, Alloc_>::value_type           value_type;
		typedef typename impl_const_if_const<value_type>::type &reference;
		typedef typename impl_const_if_const<value_type>::type *pointer;
		typedef typename allocator_type::difference_type        difference_type;
		typedef std::bidirectional_iterator_tag                 iterator_category;

		typedef typename impl_const_if_const<node>::type *nodeptr;

		nodeptr parent_, node_;

	private:
		inline void impl_normalize() {
			if (Tree_) {
				while((!node_) && parent_ && (parent_->parent)) {
					node_ = parent_->next;
					parent_ = parent_->parent;
				}
			}
		}

		inline void impl_move_forward() {
			if (Tree_) {
				if (node_) {
					parent_ = node_->parent;
					if (node_->first)
						*this = begin();
					else {
						node_ = node_->next;
						impl_normalize();
					}
				}
			} else
				node_ = node_->next;
		}

		inline void impl_move_backwards() {
			if (Tree_) {
				if (!node_) {
					node_ = parent_->last;
					if (!node_)
						*this = parent();
					else while (node_->last) {
						parent_ = node_;
						node_   = node_->last;
					}
				} else if (node_->prev) {
					parent_ = node_->parent;
					node_ = node_->prev;
					while (node_->last) {
						parent_ = node_;
						node_   = node_->last;
					}
				} else
					*this = parent();
			} else {
				if (node_)
					node_ = node_->prev;
				else
					node_ = parent_->last;
			}
		}

	public:
		iterator_common_base(nodeptr parent_, nodeptr node_) : parent_(parent_), node_(node_) { impl_normalize(); }

		// fore and back navigation
		self_t &operator++() {if (Reverse_) impl_move_backwards(); else impl_move_forward(); return static_cast<self_t&>(*this); }
		self_t operator++(int) { self_t tmp = static_cast<self_t&>(*this); operator++(); return tmp; }
		self_t &operator--() { if (Reverse_) impl_move_forward(); else impl_move_backwards(); return static_cast<self_t&>(*this); }
		self_t operator--(int) { self_t tmp = static_cast<self_t&>(*this); operator--(); return tmp; }

		// up and down navigation
		self_t parent() const { return self_t(node_->parent->parent, node_->parent); }
		self_t begin() const { return self_t(node_, node_->first); }
		self_t end() const { return iterator(node_, 0); }

		// getter
		reference operator*() const { return node_->value; }
		pointer   operator->() const { return &(node_->value); }

		// conversion to base iterator
		base_t base() const {
			return node_ ? base_t(node_->parent, node_) : base_t(parent_, 0); }

		// comparison
		bool operator==(const self_t &other) const {
			if (node_ || other.node_) return (node_ == other.node_);
			else return (parent_ == other.parent_);
		}
		bool operator!=(const self_t &other) const { return !operator==(other); }
		bool operator<(const self_t &other) const { return (node_ || other.node_) ? node_ < other.node_ : parent_ < other.parent_; }

		// node info
		size_type size() const { return node_->size; }
		depth_type depth() const {
			depth_type d=0;
			nodeptr parent = node_->parent;
			while ((parent = parent->parent)) ++d; // fails for the root node!
			return d;
		}
	};

	//////////////////////////////////////////////////////////////////////////

	template<bool Reverse_, bool Tree_> struct iterator_const_base;
	template<bool Reverse_, bool Tree_> struct iterator_nonconst_base : public iterator_common_base<false, Reverse_, Tree_> {
		typedef typename iterator_common_base<false, Reverse_, Tree_>::self_t            self_t;
		typedef typename iterator_common_base<false, Reverse_, Tree_>::base_t            base_t;
		typedef typename iterator_common_base<false, Reverse_, Tree_>::value_type        value_type;
		typedef typename iterator_common_base<false, Reverse_, Tree_>::reference         reference;
		typedef typename iterator_common_base<false, Reverse_, Tree_>::pointer           pointer;
		typedef typename iterator_common_base<false, Reverse_, Tree_>::difference_type   difference_type;
		typedef typename iterator_common_base<false, Reverse_, Tree_>::iterator_category iterator_category;
		typedef typename iterator_common_base<false, Reverse_, Tree_>::nodeptr           nodeptr;

		using iterator_common_base<false, Reverse_, Tree_>::operator++;
		using iterator_common_base<false, Reverse_, Tree_>::operator--;
		using iterator_common_base<false, Reverse_, Tree_>::operator==;
		using iterator_common_base<false, Reverse_, Tree_>::operator!=;
		using iterator_common_base<false, Reverse_, Tree_>::operator<;
		using iterator_common_base<false, Reverse_, Tree_>::operator*;
		using iterator_common_base<false, Reverse_, Tree_>::operator->;
		using iterator_common_base<false, Reverse_, Tree_>::parent;
		using iterator_common_base<false, Reverse_, Tree_>::begin;
		using iterator_common_base<false, Reverse_, Tree_>::end;
		using iterator_common_base<false, Reverse_, Tree_>::size;
		using iterator_common_base<false, Reverse_, Tree_>::depth;
		using iterator_common_base<false, Reverse_, Tree_>::base;

		iterator_nonconst_base() : iterator_common_base<false, Reverse_, Tree_>(0, 0) {}
		iterator_nonconst_base(nodeptr parent_, nodeptr node_) : iterator_common_base<false, Reverse_, Tree_>(parent_, node_) {}
		iterator_nonconst_base(const typename iterator_base<false, false, false>::type &base) : iterator_common_base<false, Reverse_, Tree_>(base.parent_, base.node_) {}

		operator iterator_const_base<Reverse_, Tree_>() const {
			return iterator_const_base<Reverse_, Tree_>(
				iterator_common_base<false, Reverse_, Tree_>::parent_,
				iterator_common_base<false, Reverse_, Tree_>::node_
			);
		}

		self_t insert(const value_type &value) const {
			nodeptr newchild;
			try {
				newchild = node::alloc();
				newchild->value = value;

				if (iterator_common_base<false, Reverse_, Tree_>::node_)
					iterator_common_base<false, Reverse_, Tree_>::node_->link_sibling(newchild);
				else
					iterator_common_base<false, Reverse_, Tree_>::parent_->link_child(newchild);

				return self_t(newchild->parent, newchild);
			} catch (...) {
				node::dealloc(newchild);
				throw;
			}
		}
		self_t        push_back(const value_type &value) const { return end().insert(value); }
		self_t        push_front(const value_type &value) const { return end().insert(value); }
		inline void   swap(self_t other) { iterator_common_base<false, Reverse_, Tree_>::node_->swap(static_cast<iterator_common_base<false, Reverse_, Tree_>&>(other).node_); }
		inline void   clear() const { iterator_common_base<false, Reverse_, Tree_>::node_->clear(); }
		self_t erase() const {
			self_t tmp = ++((*this).base());
			node::dealloc(iterator_common_base<false, Reverse_, Tree_>::node_);
			return tmp;
		}

		template<bool R, bool T> iterator_nonconst_base<R, T> copy_to(iterator_common_base<false, R, T> to) {
			nodeptr subtree = iterator_common_base<false, Reverse_, Tree_>::node_->clone();
			try {
				if (to.node_)
					to.node_->link_sibling(subtree);
				else
					to.parent_->link_child(subtree);
			} catch(...) {
				node::dealloc(subtree);
				throw;
			}
			return typename iterator_base<false, R, T>::type(subtree->parent, subtree);
		}

		template<bool R, bool T> iterator_nonconst_base<R, T> move_to(iterator_common_base<false, R, T> to) {
			nodeptr prt = to.node_;
			if (prt)
				prt = to.parent_;
			bool is_child = false;
			while (prt) {
				if (prt == iterator_common_base<false, Reverse_, Tree_>::node_) {
					is_child = true;
					break;
				}
				prt = prt->parent;
			}
			if (is_child)
				; // would create cyclic structure - do nothing (or throw or whatever
			else {
				if (to.node_)
					to.node_->link_sibling(iterator_common_base<false, Reverse_, Tree_>::node_);
				else
					to.parent_->link_child(iterator_common_base<false, Reverse_, Tree_>::node_);
			}
			return typename iterator_base<false, R, T>::type(iterator_common_base<false, Reverse_, Tree_>::node_->parent, iterator_common_base<false, Reverse_, Tree_>::node_);
		}
	};

	//////////////////////////////////////////////////////////////////////////

	template<bool Reverse_, bool Tree_> struct iterator_const_base : public iterator_common_base<true, Reverse_, Tree_> {
		typedef typename iterator_common_base<true, Reverse_, Tree_>::self_t            self_t;
		typedef typename iterator_common_base<true, Reverse_, Tree_>::base_t            base_t;
		typedef typename iterator_common_base<true, Reverse_, Tree_>::value_type        value_type;
		typedef typename iterator_common_base<true, Reverse_, Tree_>::reference         reference;
		typedef typename iterator_common_base<true, Reverse_, Tree_>::pointer           pointer;
		typedef typename iterator_common_base<true, Reverse_, Tree_>::difference_type   difference_type;
		typedef typename iterator_common_base<true, Reverse_, Tree_>::iterator_category iterator_category;
		typedef typename iterator_common_base<true, Reverse_, Tree_>::nodeptr           nodeptr;

		using iterator_common_base<true, Reverse_, Tree_>::operator++;
		using iterator_common_base<true, Reverse_, Tree_>::operator--;
		using iterator_common_base<true, Reverse_, Tree_>::operator==;
		using iterator_common_base<true, Reverse_, Tree_>::operator!=;
		using iterator_common_base<true, Reverse_, Tree_>::operator<;
		using iterator_common_base<true, Reverse_, Tree_>::operator*;
		using iterator_common_base<true, Reverse_, Tree_>::operator->;
		using iterator_common_base<true, Reverse_, Tree_>::parent;
		using iterator_common_base<true, Reverse_, Tree_>::begin;
		using iterator_common_base<true, Reverse_, Tree_>::end;
		using iterator_common_base<true, Reverse_, Tree_>::size;
		using iterator_common_base<true, Reverse_, Tree_>::depth;
		using iterator_common_base<true, Reverse_, Tree_>::base;

		iterator_const_base() : iterator_common_base<true, Reverse_, Tree_>(0, 0) {}
		iterator_const_base(nodeptr parent_, nodeptr node_) : iterator_common_base<true, Reverse_, Tree_>(parent_, node_) {}
		iterator_const_base(const typename iterator_base<false, false, false>::type &base) : iterator_common_base<true, Reverse_, Tree_>(base.parent_, base.node_) {}
		iterator_const_base(const typename iterator_base<true , false, false>::type &base) : iterator_common_base<true, Reverse_, Tree_>(base.parent_, base.node_) {}

		template<bool R, bool T> iterator_nonconst_base<R, T> copy_to(iterator_common_base<false, R, T> to) {
			nodeptr subtree = iterator_common_base<false, Reverse_, Tree_>::node_->clone();
			try {
				if (to.node_)
					to.node_->link_sibling(subtree);
				else
					to.parent_->link_child(subtree);
			} catch(...) {
				node::dealloc(subtree);
				throw;
			}
			return typename iterator_base<false, R, T>::type(subtree->parent, subtree);
		}
	};

	//////////////////////////////////////////////////////////////////////////

	template<bool R, bool T> struct iterator_base<false, R, T> {
		typedef iterator_nonconst_base<R, T> type;
	};

	template<bool R, bool T> struct iterator_base<true, R, T> {
		typedef iterator_const_base<R, T> type;
	};

	//////////////////////////////////////////////////////////////////////////

	typedef typename iterator_base<false, false, false>::type iterator;
	typedef typename iterator_base<true , false, false>::type const_iterator;
	typedef typename iterator_base<false, true , false>::type reverse_iterator;
	typedef typename iterator_base<true , true , false>::type const_reverse_iterator;
	typedef typename iterator_base<false, false, true >::type tree_iterator;
	typedef typename iterator_base<true , false, true >::type const_tree_iterator;
	typedef typename iterator_base<false, true , true >::type reverse_tree_iterator;
	typedef typename iterator_base<true , true , true >::type const_reverse_tree_iterator;

	tree() {}
	tree(const tree<T_, Alloc_> &other) {
		node *copy = other.root_.clone();
		root_.swap(copy);
		node::dealloc(copy);
	}
	~tree() {}

	void swap(tree<T_, Alloc_> &other) { root_.swap(&other.root_); }

	iterator                    begin  ()       { return iterator                   (&root_, root_.first); }
	const_iterator              begin  () const { return const_iterator             (&root_, root_.first); }
	tree_iterator               tbegin ()       { return tree_iterator              (&root_, root_.first); }
	const_tree_iterator         tbegin () const { return const_tree_iterator        (&root_, root_.first); }
	reverse_iterator            rend   ()       { return reverse_iterator           (&root_, root_.first); }
	const_reverse_iterator      rend   () const { return const_reverse_iterator     (&root_, root_.first); }
	reverse_tree_iterator       rtend  ()       { return reverse_tree_iterator      (&root_, root_.first); }
	const_reverse_tree_iterator rtend  () const { return const_reverse_tree_iterator(&root_, root_.first); }
	iterator                    end    ()       { return iterator                   (&root_, 0); }
	const_iterator              end    () const { return const_iterator             (&root_, 0); }
	tree_iterator               tend   ()       { return tree_iterator              (&root_, 0); }
	const_tree_iterator         tend   () const { return const_tree_iterator        (&root_, 0); }
	reverse_iterator            rbegin ()       { return reverse_iterator           (&root_, 0); }
	const_reverse_iterator      rbegin () const { return const_reverse_iterator     (&root_, 0); }
	reverse_tree_iterator       rtbegin()       { return reverse_tree_iterator      (&root_, 0); }
	const_reverse_tree_iterator rtbegin() const { return const_reverse_tree_iterator(&root_, 0); }
	size_type size() const { return root_.size; }

	template<bool R, bool T> inline iterator_nonconst_base<R, T> insert    (iterator_nonconst_base<R, T> pos, const value_type &value) { return pos.insert(value); }
	template<bool R, bool T> inline iterator_nonconst_base<R, T> push_back (iterator_nonconst_base<R, T> pos, const value_type &value) { return pos.push_back(value); }
	template<bool R, bool T> inline iterator_nonconst_base<R, T> push_front(iterator_nonconst_base<R, T> pos, const value_type &value) { return pos.push_front(value); }
	template<bool R, bool T> inline iterator_nonconst_base<R, T> erase     (iterator_nonconst_base<R, T> pos) { return pos.erase(); }

	inline iterator push_back(const value_type &value) { return end().insert(value); }
	inline iterator push_front(const value_type &value) { return begin().insert(value); }

	template<bool R1, bool T1, bool R2, bool T2>
	inline iterator_nonconst_base<R2, T2> copy(iterator_nonconst_base<R1, T1> from, iterator_nonconst_base<R2, T2> to) {
		return from.copy_to(to);
	}
	template<bool R1, bool T1, bool R2, bool T2>
	inline iterator_nonconst_base<R2, T2> copy(iterator_const_base<R1, T1> from, iterator_nonconst_base<R2, T2> to) {
		return from.copy_to(to);
	}
	template<bool R1, bool T1, bool R2, bool T2>
	inline iterator_nonconst_base<R2, T2> move(iterator_nonconst_base<R1, T1> from, iterator_nonconst_base<R2, T2> to) {
		return from.move_to(to);
	}

	template<bool R, bool T> inline void swap(typename iterator_base<false, R, T>::type a, typename iterator_base<false, R, T>::type b) { a.swap(b); }
	void clear() { root_.clear(); }

	tree<T_, Alloc_> &operator=(const tree<T_, Alloc_> &other) { clear(); tree<T_, Alloc_> tmptree(other); swap(tmptree); return *this; }

	inline void splice(iterator to_pos, tree<T_, Alloc_> &, iterator begin, iterator end) { while (begin != end) (begin++).move_to(to_pos); }
	inline void splice(iterator to_pos, tree<T_, Alloc_> &, iterator i) { i.move_to(to_pos); }
	inline void splice(iterator to_pos, tree<T_, Alloc_> &to_tree) { splice(to_pos, to_tree, begin(), end()); }
};

}

#endif // SGE_TREE_HPP_INCLUDED
