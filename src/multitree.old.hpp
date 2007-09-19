#include <cassert>
#include <iterator>
#include <memory>
#include <boost/iterator/iterator_facade.hpp>

#include <iostream>

template<typename T, typename A = std::allocator<T> > class multi_tree {
public:
	typedef T value_type;
	typedef A allocator_type;
	typedef typename allocator_type::size_type size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
private:
	struct node_base {
		typedef node_base* node_pointer;
		node_base(const node_pointer parent,
		          const node_pointer prev,
		          const node_pointer next)
		: parent(parent),
		  prev(prev),
		  next(next)
		{}
		
		node_pointer parent,
		             prev,
		             next;
	};

	struct node : node_base {
		node(node_base* const parent,
		     node_base* const prev,
		     node_base* const next,
		     const_reference value)
		: node_base(parent,
		            prev,
		            next),
		  children_head(this, 0, 0),
		  value(value)
		{}

		void init_children()
		{
			children_head.next = children_head.prev = &children_head;
		}
	
		node_base    children_head;
		value_type   value;
	};
	
	typedef typename allocator_type::template rebind<node>::other node_allocator_type;

	template<typename Derived, typename ValueType, typename Reference>
	class iterator_base : public boost::iterator_facade<Derived, ValueType, std::bidirectional_iterator_tag, Reference, difference_type> { 
		friend class boost::iterator_core_access;
		friend class multi_tree;
	protected:
		iterator_base(node_base *const n)
		: n(n)
		{}
		
		node_base*& mine()
		{
			return n;
		}

		node_base* mine() const
		{
			return n;
		}

		template<typename OtherDerived, typename OtherValueType, typename OtherReference>
		bool operator==(const iterator_base<OtherDerived, OtherValueType, OtherReference>& other) const
		{
			return equal(iterator_base(other.mine()));
		}
	private:
		bool equal(const iterator_base& r) const
		{
			return mine() == r.mine();
		}
		
		reference dereference() const
		{
			return static_cast<node*>(mine())->value;
		}
		
		node_base *n;
	};
public:
	class list {
	public:
		typedef typename multi_tree::value_type value_type;
		typedef typename multi_tree::allocator_type allocator_type;
		typedef typename multi_tree::size_type size_type;
		typedef typename multi_tree::difference_type difference_type;
		typedef typename multi_tree::reference reference;
		typedef typename multi_tree::const_reference const_reference;
		typedef typename multi_tree::pointer pointer;
		typedef typename multi_tree::const_pointer const_pointer;
		
		template<typename ValueType, typename Reference>
		class iterator_impl : public iterator_base<iterator_impl<ValueType, Reference>, ValueType, Reference> {
			friend class boost::iterator_core_access;
			typedef iterator_base<iterator_impl<ValueType, Reference>, ValueType, Reference> base_type;
		public:
			void increment()
			{
				mine() = mine()->next;
			}

			void decrement()
			{
				mine() = mine()->prev;
			}
			
			template<typename OtherBase, typename OtherValueType, typename OtherReference>
			explicit iterator_impl(const iterator_base<OtherBase, OtherValueType, OtherReference>& base)
			: base_type(base.mine())
			{}
		private:
			friend class list;
			friend class multi_tree;

			explicit iterator_impl(node_base* const n)
			: base_type(n)
			{}
			
			using base_type::mine;
		};

		typedef iterator_impl<value_type, reference> iterator;
		typedef iterator_impl<const value_type, const_reference> const_iterator;

		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		
		iterator begin()
		{
			return iterator(head()->next);
		}

		iterator end()
		{
			return iterator(head());
		}

		const_iterator begin() const
		{
			return const_iterator(head()->next);
		}

		const_iterator end() const
		{
			return const_iterator(head());
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
	
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		iterator insert(const iterator it, const_reference val)
		{
			assert(a != 0);

			node_base *const n = it.mine();

			node *const new_node = a->allocate(1);
			a->construct(new_node, node(parent, n->prev, n, val));
			new_node->init_children();
			
			n->prev->next = new_node;
			n->prev = new_node;
			return iterator(new_node);
		}

		iterator erase(const iterator it)
		{
			assert(a != 0);

			node* const n = static_cast<node*>(it.n);

			n->next->prev = n->prev;
			n->prev->next = n->next;

			node_base* const nnext = n->next;

			list(it.mine(), a).clear();

			a->destroy(n);
			a->deallocate(n, 1);
			return iterator(nnext);
		}

		iterator erase(iterator beg, const iterator end)
		{
			while(beg != end)
				beg = erase(beg);
			return beg;
		}

		void clear()
		{
			erase(begin(), end());
		}

		void push_front(const_reference val)
		{
			insert(begin(), val);
		}

		void push_back(const_reference val)
		{
			insert(end(), val);
		}

		void pop_front()
		{
			erase(begin());
		}

		void pop_back()
		{
			erase(--end());
		}

		reference front()
		{
			return *begin();
		}

		const_reference front() const
		{
			return *begin();
		}

		reference back()
		{
			return *--end();
		}

		const_reference back() const
		{
			return *--end();
		}

		size_type size() const
		{
			return std::distance(begin(),end());
		}

		bool empty() const
		{
			return size()==0;
		}
	private:
		explicit list(node_base *const parent, node_allocator_type *const a)
		 : parent(parent),
		   a(a)
		{}

		node_base* head() const
		{
			return &static_cast<node*>(parent)->children_head;
		}

		friend class multi_tree;

		node_base *parent;
		node_allocator_type *a;
	};

	// TODO: + const list

	template<typename ValueType, typename Reference>
	class iterator_impl : public iterator_base<iterator_impl<ValueType, Reference>, ValueType, Reference> {
		friend class boost::iterator_core_access;
		typedef iterator_base<iterator_impl<ValueType, Reference>, ValueType, Reference> base_type;
	public:
		void increment()
		{
			// if this node has children, fall into the first one
			list l(mine(), 0);
			if(!l.empty())
			{
				std::cout << "falling\n";
				mine() = l.begin().mine();
				return;
			}

			// as long as this node is the rightmost leaf, climb up
			while(mine()->parent->parent != 0 && --list(mine()->parent, 0).end() == *this)
			{
				std::cout << "climbing\n";
				mine() = mine()->parent;
			}

			std::cout << "goto right\n";
			// go into the next adjacent sibling
			mine() = mine()->next;
		}

		void decrement()
		{
		}
	
		template<typename OtherBase, typename OtherValueType, typename OtherReference>
		explicit iterator_impl(const iterator_base<OtherBase, OtherValueType, OtherReference>& base)
		: base_type(base.mine())
		{}
	private:
		friend class multi_tree;

		using base_type::mine;

		explicit iterator_impl(node_base* const n)
		: base_type(n)
		{}
	};

	typedef iterator_impl<value_type, reference> iterator;
	typedef iterator_impl<const value_type, const_reference> const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


	multi_tree(const allocator_type& a = allocator_type())
	: impl(a)
	{}

	~multi_tree()
	{
		clear();
	}

	iterator begin()
	{
		return iterator(head().begin());
	}

	iterator end()
	{
		return iterator(head().end());
	}

	const_iterator begin() const
	{
		return const_iterator(head().begin());
	}

	const_iterator end() const
	{
		return const_iterator(head().end());
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	size_type size() const
	{
		std::distance(begin(),end());
	}

	bool empty() const
	{
		return size()==0;
	}

	size_type max_size() const
	{
		return impl.a.max_size();
	}

	iterator erase(const iterator it)
	{
		return iterator(list(it.mine()->parent, &impl.a).erase(typename list::iterator(it.mine())));
	}

	void erase(iterator beg, const iterator end)
	{
		while(beg != end)
			beg = erase(beg);
	}

	void clear()
	{
		erase(begin(), end());
	}

	template<typename Derived, typename ValueType, typename Reference>
	list children(iterator_base<Derived, ValueType, Reference> const& it)
	{
		return list(it.mine(), &impl.a);
	}

	list head()
	{
		return children(iterator(impl.head));
	}
private:
	struct tree_impl {
		tree_impl(allocator_type const& na)
		: a(na),
		  head(a.allocate(1))
		{
			head->next = head;
			head->prev = head;
			head->parent = 0;

			head->init_children();
			head->children_head.parent = head;
		}

		~tree_impl()
		{
			a.deallocate(head, 1);
		}

		node_allocator_type a;
		node *head;
	};

	tree_impl impl;
};

// TODO: remove me

#include <iostream>

int main()
{
	typedef multi_tree<int> tree;
	tree t;
	tree::list l(t.head());
	l.push_back(10);
	l.push_back(11);
//	tree::iterator it = t.begin();
//	t.erase(++it);
//	l.erase(l.begin());
//	l.pop_front();
//	l.pop_back();
/*	tree::list l2(t.children(l.begin()));
	l2.push_back(20);
	l2.pop_back();*/
//	for(tree::iterator it = t.begin(); it != t.end(); ++it)
	for(tree::iterator it = t.begin(); it != t.end(); ++it)
		std::cout << *it << std::endl;
//	std::cout << *++it << std::endl;
}
