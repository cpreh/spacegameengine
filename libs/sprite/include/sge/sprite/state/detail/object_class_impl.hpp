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


#ifndef SGE_SPRITE_STATE_DETAIL_OBJECT_CLASS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_OBJECT_CLASS_IMPL_HPP_INCLUDED

#include <fcppt/record/element.hpp>
#include <fcppt/record/object_impl.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace state
{
namespace detail
{

template<
	typename StateChoices
>
struct object_class_impl
{
private:
	template<
		typename Type
	>
	struct object_class_element
	{
		typedef
		fcppt::record::element<
			typename
			Type::role,
			typename
			boost::mpl::if_<
				typename
				Type::persistent,
				typename
				Type::state_type,
				fcppt::optional::object<
					typename
					Type::state_type
				>
			>::type
		> type;
	};
public:
	typedef
	fcppt::record::object<
		typename
		boost::mpl::transform<
			typename
			StateChoices::optional_elements,
			object_class_element<
				boost::mpl::_1
			>
		>::type
	>
	type;
};

}
}
}
}

#endif
