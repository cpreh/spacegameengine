/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_DETAIL_DEFAULT_INITIALIZE_CLASS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_DEFAULT_INITIALIZE_CLASS_IMPL_HPP_INCLUDED

#include <sge/sprite/detail/default_initialize_class_element.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/algorithm/transformation/push_back.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/next.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	bool Done
>
struct default_initialize_class_impl;

template<>
struct default_initialize_class_impl<
	true
>
{
	template<
		typename Iterator,
		typename EndIterator,
		typename Object
	>
	struct result_type
	{
		typedef Object const type;
	};

	template<
		typename Iterator,
		typename EndIterator,
		typename Object
	>
	static
	Object const
	execute(
		Object const &_object
	)
	{
		return _object;
	}
};

template<>
struct default_initialize_class_impl<
	false
>
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

	template<
		typename Iterator,
		typename EndIterator,
		typename Object
	>
	struct result_type
	:
		sge::sprite::detail::default_initialize_class_impl<
			std::is_same<
				typename boost::mpl::next<
					Iterator
				>::type,
				EndIterator
			>::value
		>:: template result_type<
			typename boost::mpl::next<
				Iterator
			>::type,
			EndIterator,
			typename boost::fusion::result_of::push_back<
				Object const,
				typename boost::mpl::deref<
					Iterator
				>::type::wrapped::type
			>::type
		>
	{
	};

FCPPT_PP_POP_WARNING

	template<
		typename Iterator,
		typename EndIterator,
		typename Object
	>
	static
	typename result_type<
		Iterator,
		EndIterator,
		Object
	>::type const
	execute(
		Object const &_object
	)
	{
		typedef typename boost::mpl::next<
			Iterator
		>::type next_iterator;

		return
			sge::sprite::detail::default_initialize_class_impl<
				std::is_same<
					next_iterator,
					EndIterator
				>::value
			>:: template execute<
				next_iterator,
				EndIterator
			>(
				boost::fusion::push_back(
					_object,
					sge::sprite::detail::default_initialize_class_element<
						typename boost::mpl::deref<
							Iterator
						>::type::wrapped::type
					>::execute()
				)
			);
	}
};

}
}
}

#endif
