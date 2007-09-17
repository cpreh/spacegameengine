#include <iterator>
#include <memory>
#include <utility>
#include <stack>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/next_prior.hpp>

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
		  children_head(this, &children_head, &children_head),
		  value(value)
		{}

		node_base    children_head;
		value_type   value;
	};
	
	typedef typename allocator_type::template rebind<node>::other node_allocator_type;
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
			class iterator_impl : public boost::iterator_facade<iterator_impl<ValueType, Reference>, ValueType, std::bidirectional_iterator_tag, Reference, difference_type> {
			friend class boost::iterator_core_access;
		public:
			reference dereference() const
			{
				return static_cast<node*>(n).value;
			}

			void increment()
			{
				n = n->next;
			}

			void decrement()
			{
				n = n->prev;
			}

			bool equal(const iterator_impl& r) const
			{
				return n == r.n;
			}
		private:
			friend class list;
			friend class multi_tree;

			iterator_impl(node_base* const n)
			: n(n)
			{}

			node_base* n;
		};

		typedef iterator_impl<value_type, reference> iterator;
		typedef iterator_impl<const value_type, const_reference> const_iterator;

		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		
		iterator begin()
		{
			return iterator(head->next);
		}

		iterator end()
		{
			return iterator(head);
		}

		const_iterator begin() const
		{
			return const_iterator(head->next);
		}

		const_iterator end() const
		{
			return const_iterator(head);
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
			node_base* const n = it.n;

			node* const new_node = a->allocate(1);
			a->construct(new_node, node(head->parent, n->prev, n, val));
			
			n->prev->next = new_node;
			n->prev = new_node;
			return iterator(new_node);
		}

		iterator erase(const iterator it)
		{
			node* const n = static_cast<node*>(it.n);

			n->next->prev = n->prev;
			n->prev->next = n->next;

			node_base* const nnext = n->next;

			a->destroy(n);
			a->deallocate(n, 1);
			return iterator(nnext);
		}

		void clear()
		{
			erase(begin(), end());
		}

		void push_front(const_reference val)
		{
			insert(begin(),val);
		}

		void push_back(const_reference val)
		{
			insert(end(),val);
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
		list(node_base* const head, node_allocator_type* const a = 0)
		 : head(head),
		   a(a)
		{}

		friend class multi_tree;

		node_base* head;
		node_allocator_type* a;
	};

	// TODO: + const list

	template<typename ValueType, typename Reference>
		class iterator_impl : public boost::iterator_facade<iterator_impl<ValueType, Reference>, ValueType, std::bidirectional_iterator_tag, Reference, difference_type> {
		friend class boost::iterator_core_access;
	public:
		reference dereference() const
		{
			return static_cast<node*>(n)->value;
		}

		void increment()
		{
			// if there are childrens fall into the first one
			list l(&static_cast<node*>(n)->children_head);
			if(!l.empty())
			{
				level.push(std::make_pair(l, l.begin()));
				n = l.begin().n;
				return;
			}
			
			// else roll the stack back until a node is found which has an unvisited child left
			while(!level.empty())
			{
				list_iterator_pair p = level.top();
				level.pop();
				++p.second;
				if(p.second != p.first.end())
				{
					n = p.second.n;
					return;
				}
			}
			
			// else there was probably an iteration not starting from begin() so just climb further up
			n = n->parent;
			list cl(&static_cast<node*>(n)->children_head);
			level.push(std::make_pair(cl, cl.begin()));
		}

		void decrement()
		{
		}
		
		bool equal(const iterator_impl& impl) const
		{
			return n == impl.n;
		}
	private:
		friend class multi_tree;

		iterator_impl(node_base* const n)
		: n(n)
		{}

		node_base* n;
		
		typedef std::pair<list, typename list::iterator> list_iterator_pair;
		typedef std::stack<list_iterator_pair> node_stack;
		node_stack level;
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
//		clear();
	}

	iterator begin()
	{
		return iterator(impl.head.next);
	}

	iterator end()
	{
		return iterator(&impl.head);
	}

	const_iterator begin() const
	{
		return const_iterator(impl.head.next);
	}

	const_iterator end() const
	{
		return const_iterator(&impl.head);
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

	iterator erase(iterator it)
	{
		const iterator ret = boost::next(it);
		list l(it.n);
		l.clear();
		return ret;
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

	list children(const typename list::iterator it)
	{
		return list(&static_cast<node*>(it.n)->children_head, &impl.a);
	}

	list head()
	{
		return list(begin().n, &impl.a);
	}
private:
	struct tree_impl {
		tree_impl(const allocator_type& na)
		: a(na),
		  head(0, &head, &head)
		{}

		node_allocator_type a;
		node_base head;
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
	tree::iterator it = t.begin();
	t.erase(++it);
//	l.erase(l.begin());
//	l.pop_front();
//	l.pop_back();
/*	tree::list l2(t.children(l.begin()));
	l2.push_back(20);
	l2.pop_back();*/
	for(tree::iterator it = t.begin(); it != t.end(); ++it)
		std::cout << *it << std::endl;
}
