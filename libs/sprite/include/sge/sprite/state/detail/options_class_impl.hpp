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


#ifndef SGE_SPRITE_STATE_DETAIL_OPTIONS_CLASS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_OPTIONS_CLASS_IMPL_HPP_INCLUDED

#include <sge/sprite/state/detail/options_class_element.hpp>
#include <majutsu/record.hpp>
#include <majutsu/role.hpp>
#include <fcppt/mpl/append.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/not.hpp>
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
struct options_class_impl
{
private:
	FCPPT_PP_PUSH_WARNING
	FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

	template<
		typename Type
	>
	struct has_option
	:
	boost::mpl::and_<
		boost::mpl::not_<
			typename
			Type::persistent
		>,
		typename
		Type::has_parameter
	>
	{
	};

	FCPPT_PP_POP_WARNING

	template<
		typename Type
	>
	struct option_class_element
	{
		typedef
		majutsu::role<
			typename
			Type::optional_extra_option,
			typename
			Type::option_role
		>
		type;
	};
public:
	typedef
	majutsu::record<
		typename
		fcppt::mpl::append<
			typename boost::mpl::transform<
				typename boost::mpl::copy_if<
					typename StateChoices::optional_elements,
					has_option<
						boost::mpl::_1
					>
				>::type,
				option_class_element<
					boost::mpl::_1
				>
			>::type,
			typename boost::mpl::transform<
				typename StateChoices::optional_elements,
				sge::sprite::state::detail::options_class_element<
					boost::mpl::_1
				>
			>::type
		>::type
	>
	type;
};

}
}
}
}

#endif
