/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#ifndef SGE_BITFIELD_IMPL_HPP_INCLUDED
#define SGE_BITFIELD_IMPL_HPP_INCLUDED

#include <sge/bitfield.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/bitwise.hpp>
#include <algorithm>

template<typename Enum, Enum Size, typename InternalType>
void sge::bitfield<Enum, Size, InternalType>::clear_bit(
	internal_type &t,
	size_type const bit)
{
	t &= ~(1 << bit);
}

template<typename Enum, Enum Size, typename InternalType>
void sge::bitfield<Enum, Size, InternalType>::set_bit(
	internal_type &t,
	size_type const bit)
{
	t |= (1 << bit);
}

template<typename Enum, Enum Size, typename InternalType>
template<typename StoredType>
sge::bitfield<Enum, Size, InternalType>::proxy_impl<StoredType>::proxy_impl(
	StoredType array,
	size_type const pos)
:
	array(array),
	pos(pos)
{}

template<typename Enum, Enum Size, typename InternalType>
template<typename StoredType>
typename sge::bitfield<Enum, Size, InternalType>::size_type
sge::bitfield<Enum, Size, InternalType>::proxy_impl<StoredType>::bit_offset(
	size_type const p)
{
	return p % element_bits;
}

template<typename Enum, Enum Size, typename InternalType>
template<typename StoredType>
typename sge::bitfield<Enum, Size, InternalType>::size_type
sge::bitfield<Enum, Size, InternalType>::proxy_impl<StoredType>::array_offset(
	size_type const p)
{
	return p / element_bits;
}

template<typename Enum, Enum Size, typename InternalType>
template<typename StoredType>
// hack for VC++
typename sge::bitfield<Enum, Size, InternalType>:: template proxy_impl<StoredType>::ref_type
sge::bitfield<Enum, Size, InternalType>::proxy_impl<StoredType>::operator=(
	value_type const b)
{
	size_type const
		index(
			array_offset(pos)
		),
		bit(
			bit_offset(pos)
		);
	if(b)
		set_bit(array[index],bit);
        else
		clear_bit(array[index],bit);
	return *this;
}

template<typename Enum, Enum Size, typename InternalType>
template<typename StoredType>
sge::bitfield<Enum, Size, InternalType>::proxy_impl<StoredType>::operator bool() const
{
	return array[array_offset(pos)] & (1 << (bit_offset(pos)));
}

template<typename Enum, Enum Size, typename InternalType>
template<typename StoredType, typename Reference>
sge::bitfield<Enum, Size, InternalType>::iterator_impl<StoredType, Reference>::iterator_impl(
	StoredType array,
	size_type const pos)
: array(array),
  pos(pos)
{}

template<typename Enum, Enum Size, typename InternalType>
template<typename StoredType, typename Reference>
void sge::bitfield<Enum, Size, InternalType>::iterator_impl<StoredType, Reference>::advance(
	difference_type const d)
{
	pos += d;
}

template<typename Enum, Enum Size, typename InternalType>
template<typename StoredType, typename Reference>
void sge::bitfield<Enum, Size, InternalType>::iterator_impl<StoredType, Reference>::increment()
{
	++pos;
}

template<typename Enum, Enum Size, typename InternalType>
template<typename StoredType, typename Reference>
void sge::bitfield<Enum, Size, InternalType>::iterator_impl<StoredType, Reference>::decrement()
{
	--pos;
}

template<typename Enum, Enum Size, typename InternalType>
template<typename StoredType, typename Reference>
bool sge::bitfield<Enum, Size, InternalType>::iterator_impl<StoredType, Reference>::equal(
	iterator_impl<StoredType, Reference> const &r) const
{
	return pos == r.pos;
}

template<typename Enum, Enum Size, typename InternalType>
template<typename StoredType, typename Reference>
Reference
sge::bitfield<Enum, Size, InternalType>::iterator_impl<StoredType, Reference>::dereference() const
{
	return proxy_impl<StoredType>(array,pos);
}

template<typename Enum, Enum Size, typename InternalType>
template<typename StoredType, typename Reference>
template<typename OtherStoredType, typename OtherReference>
sge::bitfield<Enum, Size, InternalType>::iterator_impl<StoredType, Reference>::iterator_impl(
	iterator_impl<OtherStoredType, OtherReference> const &r)
:
	array(r.array),
	pos(r.pos)
{}

/*template<typename Enum, Enum Size, typename InternalType>
sge::bitfield<Enum, Size, InternalType>
sge::operator| (
	Enum const a, 
	Enum const b)
{
	return bitfield(a) | b;
}*/
	
template<typename Enum, Enum Size, typename InternalType>
sge::bitfield<Enum, Size, InternalType>::bitfield()
: array()
{}

template<typename Enum, Enum Size, typename InternalType>
sge::bitfield<Enum, Size, InternalType>::bitfield(
	Enum const e)
: array()
{
	set(e, true);
}
	
template<typename Enum, Enum Size, typename InternalType>
sge::bitfield<Enum, Size, InternalType> &
sge::bitfield<Enum, Size, InternalType>::operator=(
	Enum const e)
{
	clear();
	set(e, true);
	return *this;
}
	
template<typename Enum, Enum Size, typename InternalType>
typename sge::bitfield<Enum, Size, InternalType>::iterator
sge::bitfield<Enum, Size, InternalType>::begin()
{
	return iterator(array, 0);
}

template<typename Enum, Enum Size, typename InternalType>
typename sge::bitfield<Enum, Size, InternalType>::const_iterator
sge::bitfield<Enum, Size, InternalType>::begin() const
{
	return const_iterator(array, 0);
}

template<typename Enum, Enum Size, typename InternalType>
typename sge::bitfield<Enum, Size, InternalType>::iterator
sge::bitfield<Enum, Size, InternalType>::end()
{
	return iterator(array, size());
}

template<typename Enum, Enum Size, typename InternalType>
typename sge::bitfield<Enum, Size, InternalType>::const_iterator
sge::bitfield<Enum, Size, InternalType>::end() const
{
	return const_iterator(array, size());
}

template<typename Enum, Enum Size, typename InternalType>
typename sge::bitfield<Enum, Size, InternalType>::reverse_iterator
sge::bitfield<Enum, Size, InternalType>::rbegin()
{
	return reverse_iterator(end());
}

template<typename Enum, Enum Size, typename InternalType>
typename sge::bitfield<Enum, Size, InternalType>::const_reverse_iterator
sge::bitfield<Enum, Size, InternalType>::rbegin() const
{
	return const_reverse_iterator(end());
}

template<typename Enum, Enum Size, typename InternalType>
typename sge::bitfield<Enum, Size, InternalType>::reverse_iterator
sge::bitfield<Enum, Size, InternalType>::rend()
{
	return reverse_iterator(begin());
}

template<typename Enum, Enum Size, typename InternalType>
typename sge::bitfield<Enum, Size, InternalType>::const_reverse_iterator
sge::bitfield<Enum, Size, InternalType>::rend() const
{
	return const_reverse_iterator(begin());
}
	
template<typename Enum, Enum Size, typename InternalType>
typename sge::bitfield<Enum, Size, InternalType>::size_type
sge::bitfield<Enum, Size, InternalType>::size() const
{
	return Size;
}

template<typename Enum, Enum Size, typename InternalType>
typename sge::bitfield<Enum, Size, InternalType>::const_reference
sge::bitfield<Enum, Size, InternalType>::operator[](
	Enum const index) const
{
	return *(begin() + index);
}

template<typename Enum, Enum Size, typename InternalType>
typename sge::bitfield<Enum, Size, InternalType>::reference
sge::bitfield<Enum, Size, InternalType>::operator[](
	Enum const index)
{
	return *(begin() + index);
}

template<typename Enum, Enum Size, typename InternalType>
sge::bitfield<Enum, Size, InternalType>&
sge::bitfield<Enum, Size, InternalType>::operator|=(
	Enum const e)
{
	set(e, true);
	return *this;
}

template<typename Enum, Enum Size, typename InternalType>
sge::bitfield<Enum, Size, InternalType>&
sge::bitfield<Enum, Size, InternalType>::operator|=(
	bitfield<Enum, Size, InternalType> const &r)
{
	namespace args = boost::phoenix::arg_names;

	std::transform(
		array.begin(),
		array.end(),
		r.array.begin(),
		array.begin(),
		args::arg1 | args::arg2
	);
	return *this;
}

template<typename Enum, Enum Size, typename InternalType>
sge::bitfield<Enum, Size, InternalType>
sge::bitfield<Enum, Size, InternalType>::operator|(
	Enum const r) const
{
	bitfield ret(*this);
	ret.set(r, true);
	return ret;
}

template<typename Enum, Enum Size, typename InternalType>
sge::bitfield<Enum, Size, InternalType>
sge::bitfield<Enum, Size, InternalType>::operator|(
	bitfield<Enum, Size, InternalType> const &r) const
{
	bitfield ret(*this);
	ret |= r;
	return ret;
}

template<typename Enum, Enum Size, typename InternalType>
sge::bitfield<Enum, Size, InternalType>&
sge::bitfield<Enum, Size, InternalType>::operator&=(
	bitfield<Enum, Size, InternalType> const &r)
{
	namespace args = boost::phoenix::arg_names;

	std::transform(
		array.begin(),
		array.end(),
		r.array.begin(),
		array.begin(),
		args::arg1 & args::arg2
	);
	return *this;
}

template<typename Enum, Enum Size, typename InternalType>
sge::bitfield<Enum, Size, InternalType>
sge::bitfield<Enum, Size, InternalType>::operator& (
	bitfield<Enum, Size, InternalType> const &r) const
{
	bitfield ret(*this);
	ret &= r;
	return ret;
}

template<typename Enum, Enum Size, typename InternalType>
typename sge::bitfield<Enum, Size, InternalType>::value_type
sge::bitfield<Enum, Size, InternalType>::operator& (
	Enum const where) const
{
	return get(where);
}

template<typename Enum, Enum Size, typename InternalType>
sge::bitfield<Enum, Size, InternalType>&
sge::bitfield<Enum, Size, InternalType>::operator^=(
	bitfield<Enum, Size, InternalType> const &r)
{
	namespace args = boost::phoenix::arg_names;
	
	std::transform(
		array.begin(),
		array.end(),
		r.array.begin(),
		array.begin(),
		args::arg1 ^ args::arg2
	);
	return *this;
}

template<typename Enum, Enum Size, typename InternalType>
sge::bitfield<Enum, Size, InternalType>
sge::bitfield<Enum, Size, InternalType>::operator^(
	bitfield<Enum, Size, InternalType> const &r) const
{
	bitfield ret(*this);
	ret ^= r;
	return ret;
}

template<typename Enum, Enum Size, typename InternalType>
sge::bitfield<Enum, Size, InternalType>
sge::bitfield<Enum, Size, InternalType>::operator~() const
{
	namespace args = boost::phoenix::arg_names;

	bitfield ret(*this);

	std::transform(
		ret.array.begin(),
		ret.array.end(),
		ret.array.begin(),
		~args::arg1
	);

	return ret;
}
	
template<typename Enum, Enum Size, typename InternalType>
void sge::bitfield<Enum, Size, InternalType>::set(
	Enum const where,
	value_type const value)
{
	(*this)[where] = value;
}

template<typename Enum, Enum Size, typename InternalType>
typename sge::bitfield<Enum, Size, InternalType>::value_type
sge::bitfield<Enum, Size, InternalType>::get(
	Enum const where) const
{
	return (*this)[where];
}

template<typename Enum, Enum Size, typename InternalType>
void sge::bitfield<Enum, Size, InternalType>::clear()
{
	array.assign(0);
}

template<typename Enum, Enum Size, typename InternalType>
bool sge::bitfield<Enum, Size, InternalType>::operator==(
	bitfield<Enum, Size, InternalType> const &r) const
{
	return std::equal(begin(), end(), r.begin());
}

template<typename Enum, Enum Size, typename InternalType>
bool sge::bitfield<Enum, Size, InternalType>::operator!=(
	bitfield<Enum, Size, InternalType> const& r) const 
{
	return !((*this)==r);
}

template<typename Enum, Enum Size, typename InternalType>
bool sge::bitfield<Enum, Size, InternalType>::boolean_test() const
{
	for (const_iterator i = begin(); i != end(); ++i)
		if (*i)
			return true;
	return false;
}

#endif
