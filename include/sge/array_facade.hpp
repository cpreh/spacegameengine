#ifndef SGE_ARRAY_FACADE_HPP_INCLUDED
#define SGE_ARRAY_FACADE_HPP_INCLUDED

#include <iterator>

namespace sge
{

template<
	typename ThisType,
	typename SizeType,
	typename Reference,
	typename Pointer,
	typename Iterator,
	typename ConstIterator>
class array_facade {
public:
	typedef ThisType this_type;
	typedef SizeType size_type;
	typedef Reference reference;
	typedef Reference const const_reference;
	typedef Pointer pointer;
	typedef Pointer const const_pointer;
	typedef Iterator iterator;
	typedef ConstIterator const_iterator;
	typedef std::reverse_iterator<
		iterator> reverse_iterator;
	typedef std::reverse_iterator<
		const_iterator> const_reverse_iterator;

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;
	
	reference operator[](size_type);
	const_reference operator[](size_type) const;
	reference at(size_type);
	const_reference at(size_type) const;
};

}

#endif
