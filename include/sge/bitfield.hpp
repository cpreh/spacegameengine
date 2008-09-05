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

#include "safe_bool.hpp"
#include <boost/iterator/iterator_facade.hpp>
#include <boost/array.hpp>
#include <iterator>
#include <limits>
#include <cstddef>

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

namespace sge
{

template<typename Enum, Enum Size, typename InternalType = unsigned>
class bitfield : public safe_bool<> {
public:
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef bool value_type;
private:
	typedef InternalType internal_type;
	static const size_type element_bits = std::numeric_limits<internal_type>::digits;
	typedef boost::array<internal_type, Size / element_bits + (Size % element_bits ? 1 : 0)> array_type;
	array_type array;

	static void clear_bit(internal_type &t, size_type bit);
	static void set_bit(internal_type &t, size_type bit);

	template<typename, typename> class iterator_impl;
	template<typename StoredType>
	class proxy_impl {
		proxy_impl(StoredType array, size_type pos);

		StoredType array;
		const size_type pos;
		template<typename, typename> friend class iterator_impl;
		static size_type bit_offset(size_type p);
		static size_type array_offset(size_type p);
	public:
		proxy_impl& operator=(value_type b);
		operator value_type() const;
	};

	typedef proxy_impl<array_type&> proxy;

	bool boolean_test() const;
public:
	typedef proxy reference;
	typedef value_type const_reference;
private:
	template<typename StoredType, typename Reference>
	struct iterator_type_helper {
		typedef boost::iterator_facade<
			iterator_impl<
				StoredType,
				Reference>,
			value_type,
			std::random_access_iterator_tag,
			Reference,
			difference_type
		> type;
	};

	template<typename StoredType, typename Reference>
	class iterator_impl : public iterator_type_helper<StoredType, Reference>::type {
		friend class bitfield;
		
		iterator_impl(
			StoredType array,
			size_type pos);

		StoredType array;
		size_type pos;
		
		friend class boost::iterator_core_access;

		void advance(difference_type d);
		void increment();
		void decrement();
		bool equal(iterator_impl const &) const;
		Reference dereference() const;

		template<typename OtherStoredType, typename OtherReference>
		friend class iterator_impl;

		typedef typename iterator_type_helper<StoredType, Reference>::type base;
	public:
		// FIXME
		//typedef typename base::value_type value_type;
		//typedef typename base::reference reference;
		//typedef typename base::difference_type difference_type;
		//typedef typename base::iterator_category iterator_category;

		template<typename OtherStoredType, typename OtherReference>
		iterator_impl(
			iterator_impl<OtherStoredType, OtherReference> const &r);
	};
public:
	typedef iterator_impl<array_type&,reference> iterator;
	typedef iterator_impl<const array_type&,const_reference> const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	
	//friend bitfield operator| (const Enum a, const Enum b) { return bitfield(a) | b; }
	
	bitfield();
	bitfield(Enum e); // TODO: make this explicit?
	
	bitfield &operator=(Enum e);

	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;
	
	size_type size() const;

	const_reference operator[](Enum index) const;
	reference operator[](Enum index);
	
	bitfield &operator|=(Enum e);
	bitfield &operator|=(bitfield const &);
	bitfield operator|(Enum r) const;
	bitfield operator|(bitfield const &) const;

	bitfield &operator&=(bitfield const &r);
	bitfield operator& (bitfield const &r) const;
	value_type operator& (Enum where) const;

	bitfield& operator^=(bitfield const &);
	bitfield operator^(bitfield const &) const;

	bitfield operator~() const;
	
	void set(
		Enum where,
		value_type value);
	value_type get(Enum where) const;

	void clear();

	bool operator==(bitfield const &) const;
	bool operator!=(bitfield const &) const;
};

}

#endif

