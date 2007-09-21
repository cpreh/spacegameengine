#ifndef SGE_TREE_HPP_INCLUDED
#define SGE_TREE_HPP_INCLUDED

#include <string>
#include <ostream>
#include <boost/ptr_container/ptr_list.hpp>

namespace sge
{

template<typename T,typename Alloc = std::allocator<void *>, typename CloneAlloc = boost::heap_clone_allocator >
class tree
{
	public:
	typedef T value_type;
	typedef T& reference; 
	typedef const T& const_reference; 
	typedef boost::ptr_list<tree,Alloc,CloneAlloc> subtree_list;
	typedef typename subtree_list::iterator iterator;
	typedef typename subtree_list::const_iterator const_iterator;
	typedef typename subtree_list::difference_type difference_type;
	typedef typename subtree_list::size_type size_type;

	private:
	value_type data_;
	subtree_list subtrees;

	public:
	tree() {}
	tree(const_reference t) : data_(t) {}
	tree(const tree &t) : data_(t.data_) 
	{ 
		for (const_iterator i = t.begin(); i != t.end(); ++i)
			subtrees.push_back(new tree(*i));
	}

	tree<T> &operator=(const tree &t)
	{
		subtrees.clear();
		data_ = t.data_;
		for (const_iterator i = t.begin(); i != t.end(); ++i)
			subtrees.push_back(new tree(*i));
		return *this;
	}

	bool operator==(const tree &r) const
	{
		if (!(data() == r.data()) || size() != r.size())
			return false;

		for (const_iterator ri = r.begin(),li = begin(); ri != r.end() && li != end(); ++ri,++li)
			if (*ri != *li)
				return false;

		return true;
	}

	bool operator!=(const tree &r) const { return !(*this == r); }

	void swap(const tree &r)
	{
		tree t = *this;
		*this = r;
		r = t;
	}

	const_reference data() const { return data_; }
	void data(const_reference t) { data_ = t; }

	tree &front() { return subtrees.front(); }
	tree &back() { return subtrees.back(); }

	const tree &front() const { return subtrees.front(); }
	const tree &back() const { return subtrees.back(); }

	iterator begin() { return subtrees.begin(); }
	iterator end() { return subtrees.end(); }

	const_iterator begin() const { return subtrees.begin(); }
	const_iterator end() const { return subtrees.end(); }

	tree &push_front(const_reference t)
	{
		subtrees.push_front(new tree(t));
		return front();
	}

	tree &push_front(const tree &t)
	{
		subtrees.push_front(new tree(t));
		return front();
	}

	tree &push_back(const_reference t)
	{
		subtrees.push_back(new tree(t));
		return subtrees.back();
	}

	tree &push_back(const tree &t)
	{
		subtrees.push_back(new tree(t));
		return subtrees.back();
	}

	void pop_back() { erase(--end()); }
	void pop_front() { erase(begin()); }

	size_type size() const { return subtrees.size(); }
	size_type max_size() const { return subtrees.max_size(); }

	bool empty() const { return size() == 0; }
	void clear() { subtrees.clear(); }
	void erase(iterator i) { subtrees.erase(i); }
	void erase(iterator i,iterator j) { subtrees.erase(i,j); }

	void remove(const_reference t) 
	{ 
		while (true)
		{
			iterator i = begin();
			for (; i != end(); ++i)
				if (i->data() == t)
					break;

			if (i == end())
				break;

			erase(i);
		}
	}

	const_iterator insert(const_iterator a,const tree &t) { return subtrees.insert(a,new tree(t)); }
	iterator insert(iterator a,const tree &t) { return subtrees.insert(a,new tree(t)); }

	tree &left_child() { return front(); }
	tree &right_child() { return back(); }

	const tree &left_child() const { return front(); }
	const tree &right_child() const { return back(); }

	template<typename Ch,typename Traits>
	std::basic_ostream<Ch,Traits> &output(std::basic_ostream<Ch,Traits> &stream,const unsigned depth) const
	{
		stream << std::basic_string<Ch,Traits>(depth*2,stream.widen(' ')) << data();

		if (size()) 
			stream << stream.widen('\n');

		for (typename tree<T>::const_iterator i = begin(); i != end(); ++i)
		{
			i->output(stream,depth+1);
			if (i != --end())
				stream << stream.widen('\n');
		}

		return stream;
	}
};

template<typename T,typename Ch,typename Traits>
inline std::basic_ostream<Ch,Traits> &operator<<(std::basic_ostream<Ch,Traits> &stream,const tree<T> &b)
{
	return b.output(stream,0);
}

}

#endif // SGE_TREE_HPP_INCLUDED
