/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_BITFIELD_HPP_INCLUDED
#define SGE_BITFIELD_HPP_INCLUDED

#include <cstddef>
#include <limits>
#include <iterator>
#include <algorithm>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/array.hpp>

// Requires:
// - Enum shall be an enumeration type that doesn't contain any enumerators with explicit values.
//   example 1: enum my_enum { value1, value2, value3 }; is perfectly valid
//   example 2: enum my_enum { value = 100 }; is NOT valid
// - Size shall be the number of enumerators defined in Enum.
//   To achieve consistency you should define the enum's size within the enum itsself.
//   example: enum my_enum { value1, value2, value3, _my_enum_size };
//            typedef bitfield<my_enum,_my_enum_size> mybitfield;
// - operator|(Enum,Enum) shall not be declared! 
// - std::numeric_limits<InternalType>::digits shall be the number of bits usable in InternalType

namespace sge {

template<typename Enum, Enum Size, typename InternalType = unsigned> class bitfield {
public:
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef bool value_type;
private:
	typedef InternalType internal_type;
	static const size_type element_bits = std::numeric_limits<internal_type>::digits;
	typedef boost::array<internal_type, Size / element_bits + (Size % element_bits ? 1 : 0)> array_type;
	array_type array;
	static void clear_bit(internal_type& t, size_type bit) { t &= ~(1 << bit); }
	static void set_bit(internal_type& t, size_type bit) { t |= (1 << bit); }

	template<typename, typename> class iterator_impl;
	template<typename StoredType>
	class proxy_impl {
		proxy_impl(StoredType array, size_type pos)
			: array(array), pos(pos) {}
		StoredType array;
		const size_type pos;
		template<typename, typename> friend class iterator_impl;
		static size_type bit_offset(size_type p) { return p % element_bits; }
		static size_type array_offset(size_type p) { return p / element_bits; }
	public:
		proxy_impl& operator=(value_type b)
		{
			const size_type index = array_offset(pos), bit = bit_offset(pos);
			if(b) set_bit(array[index],bit);
		        else clear_bit(array[index],bit);
			return *this;
		}
		operator value_type() const { return array[array_offset(pos)] & (1 << (bit_offset(pos))); }
	};

	template <typename T>
	struct bit_and : public std::binary_function<T,T,T> { T operator()(const T& x, const T& y) const { return x & y; } };

	template <typename T>
	struct bit_or : public std::binary_function<T,T,T> { T operator()(const T& x, const T& y) const { return x | y; } };

	template <typename T>
	struct bit_xor : public std::binary_function<T,T,T> { T operator()(const T& x, const T& y) const { return x ^ y; } };

	template <typename T>
	struct bit_not : public std::unary_function<T,T> { T operator()(const T& x) const { return ~x; } }; 

	typedef proxy_impl<array_type&> proxy;
public:
	typedef proxy reference;
	typedef const value_type const_reference;
private:
	template<typename StoredType, typename Reference>
	class iterator_impl : public boost::iterator_facade<iterator_impl<StoredType,Reference>,value_type,std::random_access_iterator_tag,Reference,difference_type> {
		friend class bitfield;
		iterator_impl(StoredType array, size_type pos)
			: array(array), pos(pos) {}
		StoredType array;
		size_type pos;
		
		friend class boost::iterator_core_access;
		void advance(difference_type d) { pos += d; }
		void increment() { ++pos; }
		void decrement() { --pos; }
		bool equal(const iterator_impl& r) const { return pos == r.pos; }
		Reference dereference() const { return proxy_impl<StoredType>(array,pos); }

		template<typename OtherStoredType, typename OtherReference> friend class iterator_impl;
	public:
		template<typename OtherStoredType, typename OtherReference> iterator_impl(const iterator_impl<OtherStoredType,OtherReference>& r)
			: array(r.array), pos(r.pos) {}
	};
public:
	typedef iterator_impl<array_type&,reference> iterator;
	typedef iterator_impl<const array_type&,const_reference> const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	
	friend bitfield operator| (const Enum a, const Enum b) { return bitfield(a) | b; }
	
	bitfield() : array() {}
	bitfield(Enum e) : array() { set(e,true); }
	
	bitfield& operator=(const Enum e)
	{
		clear();
		set(e,true);
	}
	
	iterator begin() { return iterator(array,0); }
	const_iterator begin() const { return const_iterator(array,0); }
	iterator end() { return iterator(array,size()); }
	const_iterator end() const { return const_iterator(array,size()); }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iteator(begin()); }
	
	size_type size() const { return Size; }

	const_reference operator[](const Enum index) const { return *(begin()+index); }
	reference operator[](const Enum index) { return *(begin()+index); }
	
	bitfield& operator|=(const Enum e) { set(e,true); return *this; }
	bitfield& operator|=(const bitfield& r) { std::transform(array.begin(),array.end(),r.array.begin(),array.begin(),bit_or<internal_type>()); return *this; }
	bitfield operator|(const Enum r) const { bitfield ret(*this); ret.set(r,true); return ret; }
	bitfield operator|(const bitfield& r) const { bitfield ret(*this); ret |= r; return ret; }

	bitfield& operator&=(const bitfield& r) { std::transform(array.begin(),array.end(),r.array.begin(),array.begin(),bit_and<internal_type>()); return *this; }
	bitfield operator& (const bitfield& r) const { bitfield ret(*this); ret &= r; return ret; }
	value_type operator& (const Enum where) const { return get(where); }

	bitfield& operator^=(const bitfield& r) { std::transform(array.begin(),array.end(),r.array.begin(),array.begin(),bit_xor<internal_type>()); return *this; }
	bitfield operator^(const bitfield& r) const { bitfield ret(*this); ret ^= r; return ret; }

	bitfield operator~() const { bitfield ret(*this); std::transform(ret.array.begin(),ret.array.end(),ret.array.begin(),bit_not<internal_type>()); return ret; }
	
	void set(const Enum where, const value_type value) { *(begin()+where) = value; }
	value_type get(const Enum where) const { return *(begin()+where); }

	void clear() { array.assign(0); }

	bool operator==(const bitfield& r) const { return std::equal(begin(),end(),r.begin()); }
	bool operator!=(const bitfield& r) const { return !((*this)==r); }
};

}

#endif

