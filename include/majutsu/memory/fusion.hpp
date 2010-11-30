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


#ifndef MAJUTSU_MEMORY_FUSION_HPP_INCLUDED
#define MAJUTSU_MEMORY_FUSION_HPP_INCLUDED

#include <majutsu/memory/detail/index_of.hpp>
#include <majutsu/memory/detail/expand_fusion_initlist.hpp>
#include <majutsu/memory/detail/init_constants.hpp>
#include <majutsu/detail/find_role.hpp>
#include <majutsu/detail/make_iterators.hpp>
#include <majutsu//role_return_type.hpp>
#include <majutsu/flatten.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/for_each.hpp>

namespace majutsu
{
namespace memory
{

template<
	typename T
>
struct inner_type {
	typedef typename T::type type;
};

template<
	typename Type
>
class fusion
{
public:
	typedef typename flatten<
		Type
	>::type types; // TODO

	typedef typename boost::fusion::result_of::as_vector<
		boost::mpl::transform_view<
			types,
			inner_type<
				boost::mpl::_1
			>
		>
	>::type tuple;

	fusion()
	:
		elements_()
	{
		boost::mpl::for_each<
			typename majutsu::detail::make_iterators<
				types	
			>::type
		>(
			detail::init_constants<
				fusion<
					Type
				>
			>(
				*this
			)
		);
	}

	explicit fusion(
		fusion const &_other
	)
	:
		elements_(
			_other.elements_
		)
	{}

	template<
		typename Arguments
	>
	explicit fusion(
		Arguments const &_elements
	)
	:
		elements_(
			detail::expand_fusion_initlist<
				types,
				tuple
			>(
				_elements
			)
		)
	{}

	template<
		typename Role
	>
	void
	set(
		typename majutsu::role_return_type<
			types,
			Role
		>::type const &_value
	)
	{
		typedef typename majutsu::detail::find_role<
			types,
			Role
		>::type found_role;

		set_internal<
			found_role
		>(
			_value
		);
	}

	template<
		typename Role
	>
	typename majutsu::role_return_type<
		types,
		Role
	>::type
	get() const
	{
		typedef typename majutsu::detail::find_role<
			types,
			Role
		>::type found_role;

		return
			boost::fusion::at<
				detail::index_of<
					types,
					found_role
				>
			>(
				elements_
			);
	}

	template<
		typename Iterator,
		typename Value
	>
	void
	set_internal(
		Value const &_value
	)
	{
		boost::fusion::at<
			detail::index_of<
				types,
				Iterator
			>
		>(
			elements_
		) = _value;
	}
private:
	tuple elements_;
};

}
}

#endif
