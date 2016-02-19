/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_DETAIL_MAKE_CLASS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_MAKE_CLASS_HPP_INCLUDED

#include <sge/sprite/detail/application.hpp>
#include <majutsu/record.hpp>
#include <majutsu/role.hpp>
#include <fcppt/mpl/flatten.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Choices
>
using make_class
=
majutsu::record<
	fcppt::mpl::flatten<
		typename
		boost::mpl::joint_view<
			typename
			boost::mpl::transform<
				typename
				Choices::optional_elements,
				sge::sprite::detail::application<
					boost::mpl::_1,
					Choices
				>
			>::type,
			boost::mpl::vector2<
				typename
				boost::mpl::apply<
					typename
					Choices::pos_choice,
					Choices
				>::type,
				typename
				boost::mpl::apply<
					typename
					Choices::size_choice,
					Choices
				>::type
			>
		>::type
	>
>;

}
}
}

#endif
