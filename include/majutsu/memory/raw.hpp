/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef MAJUTSU_MEMORY_RAW_HPP_INCLUDED
#define MAJUTSU_MEMORY_RAW_HPP_INCLUDED

#include <majutsu/memory/detail/index_of.hpp>
#include <majutsu/memory/detail/store.hpp>
#include <majutsu/memory/detail/init_constants.hpp>
#include <majutsu/memory/detail/init_raw_memory.hpp>
#include <majutsu/memory/needs_init.hpp>
#include <majutsu/detail/find_role.hpp>
#include <majutsu/detail/make_iterators.hpp>
#include <majutsu/detail/wrapped_type.hpp>
#include <majutsu/concepts/dynamic_memory/place.hpp>
#include <majutsu/concepts/dynamic_memory/make.hpp>
#include <majutsu/concepts/dynamic_memory/needed_size.hpp>
#include <majutsu/is_constant.hpp>
#include <majutsu/is_role.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/raw_data.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/flatten.hpp>
#include <majutsu/access_role.hpp>
#include <majutsu/role_return_type.hpp>
#include <fcppt/container/array.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/algorithm/transformation/zip.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <numeric>
#include <algorithm>

namespace majutsu
{
namespace memory
{

template<
	typename Type
>
class raw
{
public:
	typedef raw_data value_type;
private:
	typedef typename flatten<
		Type
	>::type flattened_types;

	typedef fcppt::container::array<
		size_type,
		boost::mpl::size<
			flattened_types
		>::value
	> size_vector;

	typedef detail::store<
		value_type
	> storage_type;
public:
	typedef flattened_types types; // TODO

	typedef raw_pointer pointer;
	typedef const_raw_pointer const_pointer;

	raw()
	:
		store_(),
		sizes_()
	{
		init();
	}

	template<
		typename Arguments
	>
	raw(
		Arguments const &arguments_
	)
	:
		store_(),
		sizes_()
	{
		init();

		typedef typename boost::mpl::remove_if<
			typename majutsu::detail::make_iterators<
				flattened_types
			>::type,
			boost::mpl::not_<
				needs_init<
					boost::mpl::deref<
						boost::mpl::_1
					>
				>
			>
		>::type types_to_init;

		boost::fusion::for_each(
			boost::fusion::zip(
				arguments_,
				types_to_init()
			),
			detail::init_raw_memory<
				raw<
					Type
				>
			>(
				*this
			)
		);
	}

	template<
		typename Role
	>
	void
	set(
		typename majutsu::role_return_type<
			flattened_types,
			Role
		>::type const &value_
	)
	{
		set_internal<
			typename majutsu::detail::find_role<
				flattened_types,
				Role
			>::type
		>(
			value_
		);
	}

	template<
		typename Role
	>
	typename majutsu::role_return_type<
		flattened_types,
		Role
	>::type
	get() const
	{
		typedef typename majutsu::detail::find_role<
			flattened_types,
			Role
		>::type role_iter;

		typedef typename boost::mpl::deref<
			role_iter
		>::type found_role;

		typedef typename access_role<
			found_role
		>::type elem;

		size_type const index(
			detail::index_of<
				flattened_types,
				role_iter	
			>::value
		);

		return
			concepts::dynamic_memory::make<
				elem
			>(
				store_.data()
				+ std::accumulate(
					sizes_.begin(),
					sizes_.begin() + index,
					0
				)
			);
	}
	
	pointer
	data()
	{
		return store_.data();
	}

	const_pointer
	data() const
	{
		return store_.data();
	}

	size_type
	size() const
	{
		return store_.size();
	}
private:
	void
	init()
	{
		std::fill(
			sizes_.begin(),
			sizes_.end(),
			0
		);

		boost::mpl::for_each<
			typename majutsu::detail::make_iterators<
				flattened_types
			>::type
		>(
			detail::init_constants<
				raw<
					Type
				>
			>(
				*this
			)
		);
	}

public:
	template<
		typename Iterator,
		typename Value
	>
	void
	set_internal(
		Value const &value_
	)
	{
		typedef typename boost::mpl::deref<
			Iterator
		>::type deref_elem;

		typedef typename majutsu::detail::wrapped_type<
			deref_elem
		>::type element;

		size_type const index(
			detail::index_of<
				flattened_types,
				Iterator
			>::value
		);

		size_type const needed_size(
			concepts::dynamic_memory::needed_size<
				element
			>(
				value_
			)
		);

		size_type const offset(
			std::accumulate(
				sizes_.begin(),
				sizes_.begin()
				+ index,
				0u
			)
		);

		storage_type::iterator const place(
			store_.begin() + offset
		);

		size_type const cur_size(
			sizes_[
				index
			]
		);

		if(
			needed_size > cur_size
		)
			store_.make_space(
				place,
				needed_size - cur_size
			);
		else
			store_.erase(
				place,
				place + cur_size - needed_size
			);

		concepts::dynamic_memory::place<
			element
		>(
			value_,
			store_.begin() + offset
		);

		sizes_[
			index
		] = needed_size;
	}
private:
	storage_type store_;

	size_vector sizes_;
};

}
}

#endif
