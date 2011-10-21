/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef MAJUTSU_MEMORY_DETAIL_INIT_FUSION_ELEMENT_HPP_INCLUDED
#define MAJUTSU_MEMORY_DETAIL_INIT_FUSION_ELEMENT_HPP_INCLUDED

#include <majutsu/is_constant.hpp>
#include <majutsu/is_role.hpp>
#include <majutsu/memory/detail/index_of.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace majutsu
{
namespace memory
{
namespace detail
{

template<
	typename Elements,
	typename Arguments
>
struct init_fusion_element
{
	template<
		typename
	>
	struct result;

	template<
		typename Elem
	>
	struct result<
		init_fusion_element(
			Elem
		)
	>
	{
		typedef typename boost::remove_const<
			typename boost::remove_reference<
				Elem
			>::type
		>::type::type type;
	};


	explicit init_fusion_element(
		Arguments const &_arguments
	)
	:
		arguments_(_arguments)
	{}

	template<
		typename Type
	>
	typename boost::enable_if<
		majutsu::is_constant<
			Type
		>,
		typename Type::type
	>::type
	operator()(
		Type const &
	) const
	{
		return Type::value;
	}

	template<
		typename Type
	>
	typename boost::enable_if<
		majutsu::is_role<
			Type
		>,
		typename Type::type
	>::type
	operator()(
		Type const &
	) const
	{
		typedef boost::mpl::filter_view<
			Elements,
			majutsu::is_role<
				boost::mpl::_1
			>
		> roles;

		return
			boost::fusion::at<
				typename index_of<
					roles,
					typename boost::mpl::find<
						roles,
						Type
					>::type
				>::type
			>(
				arguments_
			);
	}

	template<
		typename Type
	>
	typename boost::disable_if<
		boost::mpl::or_<
			majutsu::is_constant<
				Type
			>,
			majutsu::is_role<
				Type
			>
		>,
		typename Type::type
	>::type
	operator()(
		Type const &
	) const
	{
		return typename Type::type();
	}
private:
	Arguments const &arguments_;
};

}
}
}

#endif
