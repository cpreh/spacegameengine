#include <iterator>
#include <memory>
#include <utility>
#include <stack>

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
		
		class iterator : public std::iterator<std::bidirectional_iterator_tag, difference_type, pointer, reference> {
		public:
			iterator& operator++()
			{
				n = n->next;
				return *this;
			}

			iterator operator++(int)
			{
				const iterator tmp(*this);
				++(*this);
				return tmp;
			}

			iterator& operator--()
			{
				n = n->prev;
				return *this;
			}

			iterator operator--(int)
			{
				const iterator tmp(*this);
				--(*this);
				return tmp;
			}

			bool operator==(const iterator& r) const
			{
				return n == r.n;
			}

			bool operator!=(const iterator& r) const
			{
				return !(*this == r);
			}

			reference operator*() const
			{
				return static_cast<node*>(n).value;
			}

			pointer operator->() const
			{
				return &static_cast<node*>(n).value;
			}
		private:
			friend class list;
			friend class multi_tree;

			iterator(node_base* const n)
			: n(n)
			{}

			node_base* n;
		};

		typedef std::reverse_iterator<iterator> reverse_iterator;
		
		// TODO: const versions

		iterator begin()
		{
			return iterator(parent->children_head.next);
		}

		iterator end()
		{
			return iterator(&parent->children_head);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		iterator insert(const iterator it, const_reference val)
		{
			node_base* const n = it.n;

			node* const new_node = a->allocate(1);
			a->construct(new_node, node(parent, n->prev, n, val));
			
			n->prev->next = new_node;
			n->prev = new_node;
			return iterator(new_node);
		}

		iterator erase(const iterator it)
		{
			node_base* const n = it.n;

			n->next->prev = n->prev;
			n->prev->next = n->next;

			node* const nnext = n->next;

			a->destroy(n);
			a->deallocate(n);
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

		size_type size() const
		{
			return std::distance(begin(),end());
		}

		bool empty() const
		{
			return size()==0;
		}
	private:
		list(node* const parent, node_allocator_type* a = 0)
		 : parent(parent),
		   a(a)
		{}

		friend class multi_tree;

		node* parent;
		node_allocator_type* a;
	};

	// TODO: + const list

	class iterator : public std::iterator<std::bidirectional_iterator_tag, difference_type, pointer, reference> {
	public:
		iterator& operator++()
		{
			// if there are childrens fall into the first one
			list l(static_cast<node*>(n));
			//if(!l.empty())
			if(l.begin()==l.end())
			{
				level.push(std::make_pair(l, l.begin()));
				n = l.begin().n;
				return *this;
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
					return *this;
				}
			}
			
			// else there was probably an iteration not starting from begin() so just climb further up
			n = n->parent;
			list cl(static_cast<node*>(n));
			level.push(std::make_pair(cl, cl.begin()));
			return *this;
		}

		iterator operator++(int)
		{
			const iterator tmp(*this);
			++(*this);
			return tmp;
		}

		iterator& operator--();

		iterator operator--(int)
		{
			const iterator tmp(*this);
			--(*this);
			return tmp;
		}

		reference operator*() const
		{
			return static_cast<node*>(n)->value;
		}

		pointer operator->() const
		{
			return &static_cast<node*>(n)->value;
		}

		bool operator==(const iterator& r) const
		{
			return n == r.n;
		}

		bool operator!=(const iterator& r) const
		{
			return !(*this == r);
		}
	private:
		friend class multi_tree;

		iterator(node_base* const n)
		: n(n)
		{}

		node_base* n;
		
		typedef std::pair<list, typename list::iterator> list_iterator_pair;
		typedef std::stack<list_iterator_pair> node_stack;
		node_stack level;
	};

	typedef std::reverse_iterator<iterator> reverse_iterator;

	// TODO: const iterators

	multi_tree(const allocator_type& a = allocator_type())
	: impl(a)
	{}

	iterator begin()
	{
		return iterator(impl.head);
	}

	iterator end()
	{
		return iterator(impl.head->next);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	// TODO: + const-versions

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

	void clear()
	{
		children(iterator(impl.head)).clear();
	}

	list children(const iterator it)
	{
		return list(static_cast<node*>(it.n), &impl.a);
	}

	list children(const typename list::iterator it)
	{
		return list(static_cast<node*>(it.n), &impl.a);
	}
private:
	struct tree_impl {
		tree_impl(const allocator_type& na)
		: a(na),
		  head(a.allocate(1))
		{
			head->parent = 0;
			head->children_head.parent = head;
			head->children_head.next = &head->children_head;
			head->children_head.prev = &head->children_head;
			head->prev = head;
			head->next = head;
		}

		node_allocator_type a;
		node* head;
	};

	tree_impl impl;
};

// TODO: remove me

#include <iostream>

int main()
{
	typedef multi_tree<int> tree;
	tree t;
	tree::list l(t.children(t.begin()));
	l.push_back(10);
	tree::list l2(t.children(l.begin()));
	l2.push_back(20);
	tree::iterator it = t.begin();
	std::cout << *(++it) << '\n';
}
