#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

#include <ostream>
#include <boost/ptr_container/ptr_list.hpp>

template<typename T>
class tree
{
	public:
	typedef T value_type;
	typedef T& reference; 
	typedef const T& const_reference; 
	typedef boost::ptr_list<tree> subtree_list;
	typedef typename subtree_list::iterator iterator;
	typedef typename subtree_list::const_iterator const_iterator;
	typedef typename subtree_list::difference_type difference_type;
	typedef typename subtree_list::size_type size_type;

	private:
	value_type data_;
	subtree_list subtrees;

	public:
	tree() {}
	tree(const value_type &t) : data_(t) {}
	tree(const tree &t) { *this = t; }
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
		if (data() != r.data() || size() != r.size())
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

	value_type data() const { return data_; }
	void data(const value_type &t) { data_ = t; }

	iterator begin() { return subtrees.begin(); }
	iterator end() { return subtrees.end(); }

	const_iterator begin() const { return subtrees.begin(); }
	const_iterator end() const { return subtrees.end(); }

	tree &push_back(const T &t)
	{
		subtrees.push_back(new tree(t));
		return subtrees.back();
	}

	tree &push_back(const tree &t)
	{
		subtrees.push_back(new tree(t));
		return subtrees.back();
	}

	size_type size() const { return subtrees.size(); }
	size_type max_size() const { return subtrees.max_size(); }

	bool empty() const { return size() == 0; }
	void clear() { subtrees.clear(); }
	void erase(iterator i) { subtrees.erase(i); }
	void erase(const T &t) { erase(std::find(subtrees.begin(),subtrees.end(),t)); }

	template<typename Ch,typename Traits>
	std::basic_ostream<Ch,Traits> &output(std::basic_ostream<Ch,Traits> &stream,const unsigned depth) const
	{
		stream << std::string(depth*2,stream.widen(' ')) << data();
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

#endif // TREE_HPP_INCLUDED
