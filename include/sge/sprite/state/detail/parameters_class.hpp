/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_STATE_DETAIL_PARAMETERS_CLASS_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_PARAMETERS_CLASS_HPP_INCLUDED

#include <majutsu/class.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <majutsu/simple.hpp>
#include <majutsu/memory/fusion.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/copy_if.hpp>
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
struct parameters_class
{
private:
	template<
		typename Type
	>
	struct has_parameter
	{
		typedef typename Type::has_parameter type;
	};

	template<
		typename Type
	>
	struct parameter_class_element
	{
		typedef majutsu::role<
			majutsu::simple<
				typename Type::optional_extra_parameters
			>,
			typename Type::parameter_role
		> type;
	};
public:
	typedef majutsu::class_<
		majutsu::composite<
			typename boost::mpl::transform<
				typename boost::mpl::copy_if<
					typename StateChoices::optional_elements,
					has_parameter<
						boost::mpl::_1
					>
				>::type,
				parameter_class_element<
					boost::mpl::_1
				>
			>::type
		>,
		majutsu::memory::fusion
	> type;
};

}
}
}
}

#endif
