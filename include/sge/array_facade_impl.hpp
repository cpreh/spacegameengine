#ifndef SGE_ARRAY_FACADE_IMPL_HPP_INCLUDED
#define SGE_ARRAY_FACADE_IMPL_HPP_INCLUDED

#include "array_facade.hpp"
#include "exception.hpp"
#include "string.hpp"

template<
	typename ThisType,
	typename SizeType,
	typename Reference,
	typename Pointer,
	typename Iterator,
	typename ConstIterator>
typename sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::iterator
sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::begin()
{
	return iterator(
		static_cast<ThisType&>(
			*this).data());
}

template<
	typename ThisType,
	typename SizeType,
	typename Reference,
	typename Pointer,
	typename Iterator,
	typename ConstIterator>
typename sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::iterator
sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::end()
{
	ThisType &me(
		static_cast<ThisType &>(
			*this));
	return const_iterator(
		me.data() + me.size());
}

template<
	typename ThisType,
	typename SizeType,
	typename Reference,
	typename Pointer,
	typename Iterator,
	typename ConstIterator>
typename sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::const_iterator
sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::begin() const
{
	return const_iterator(
		const_cast<ThisType &>(
			*this).	begin());
}

template<
	typename ThisType,
	typename SizeType,
	typename Reference,
	typename Pointer,
	typename Iterator,
	typename ConstIterator>
typename sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::const_iterator
sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::end() const
{
	return const_iterator(
		const_cast<ThisType &>(
			*this).end());
}

template<
	typename ThisType,
	typename SizeType,
	typename Reference,
	typename Pointer,
	typename Iterator,
	typename ConstIterator>
typename sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::reverse_iterator
sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::rbegin()
{
	return reverse_iterator(
		end());
}

template<
	typename ThisType,
	typename SizeType,
	typename Reference,
	typename Pointer,
	typename Iterator,
	typename ConstIterator>
typename sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::reverse_iterator
sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::rend()
{
	return reverse_iterator(
		begin());
}

template<
	typename ThisType,
	typename SizeType,
	typename Reference,
	typename Pointer,
	typename Iterator,
	typename ConstIterator>
typename sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::const_reverse_iterator
sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::rbegin() const
{
	return const_reverse_iterator(
		const_cast<ThisType &>(
			*this).rbegin());
}

template<
	typename ThisType,
	typename SizeType,
	typename Reference,
	typename Pointer,
	typename Iterator,
	typename ConstIterator>
typename sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::const_reverse_iterator
sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::rend() const
{
	return const_reverse_iterator(
		const_cast<ThisType &>(
			*this).rend());
}

template<
	typename ThisType,
	typename SizeType,
	typename Reference,
	typename Pointer,
	typename Iterator,
	typename ConstIterator>
typename sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::reference
sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::operator[](
		const size_type i)
{
	return *(begin() + i);
}

template<
	typename ThisType,
	typename SizeType,
	typename Reference,
	typename Pointer,
	typename Iterator,
	typename ConstIterator>
typename sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::const_reference
sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::operator[](
		const size_type i) const
{
	return const_cast<ThisType &>(
		*this)[i];;
}

template<
	typename ThisType,
	typename SizeType,
	typename Reference,
	typename Pointer,
	typename Iterator,
	typename ConstIterator>
typename sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::reference
sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::at(
		const size_type i)
{
	if(i >= static_cast<ThisType &>(*this).size())
		throw exception(
			SGE_TEXT("array_facade::at(): index out of range!"));
	return (*this)[i];
}

template<
	typename ThisType,
	typename SizeType,
	typename Reference,
	typename Pointer,
	typename Iterator,
	typename ConstIterator>
typename sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::const_reference
sge::array_facade<
	ThisType,
	SizeType,
	Reference,
	Pointer,
	Iterator,
	ConstIterator>::at(
		const size_type i) const
{
	return const_cast<ThisType &>(
		*this).at(i);
}

#endif
