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


#ifndef SGE_SYSTEMS_DETAIL_MAKE_LIST_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_MAKE_LIST_HPP_INCLUDED

#include <sge/systems/list_impl.hpp>
#include <sge/systems/detail/add_defaults.hpp>
#include <sge/systems/detail/any_map.hpp>
#include <sge/systems/detail/extract_needs_init.hpp>
#include <sge/systems/detail/extract_parameter_type.hpp>
#include <sge/systems/detail/list.hpp>
#include <sge/systems/detail/make_list_visitor.hpp>
#include <fcppt/static_assert_expression.hpp>
#include <fcppt/mpl/all_of.hpp>
#include <fcppt/mpl/for_each.hpp>
#include <fcppt/mpl/for_each.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

template<
	typename Choices,
	typename Inits
>
sge::systems::detail::list const
make_list(
	sge::systems::list<
		Inits
	> const &_init
)
{
	sge::systems::detail::list result;

	// Initialize every subsystem given in the parameters
	boost::fusion::for_each(
		_init.get(),
		sge::systems::detail::make_list_visitor<
			Choices,
			Inits
		>(
			result
		)
	);

	// For every subsystem that doesn't need initialization and is not
	// initialized, add a default parameter
	fcppt::mpl::for_each<
		boost::mpl::filter_view<
			boost::mpl::filter_view<
				Choices,
				boost::mpl::not_<
					sge::systems::detail::extract_needs_init<
						boost::mpl::_1
					>
				>
			>,
			boost::mpl::not_<
				boost::mpl::contains<
					Inits,
					sge::systems::detail::extract_parameter_type<
						boost::mpl::_1
					>
				>
			>
		>
	>(
		sge::systems::detail::add_defaults(
			result
		)
	);

	// Check that every subsystem that needs initialization is initialized
	FCPPT_STATIC_ASSERT_EXPRESSION((
		fcppt::mpl::all_of<
			boost::mpl::filter_view<
				Choices,
				sge::systems::detail::extract_needs_init<
					boost::mpl::_
				>
			>,
			boost::mpl::contains<
				Inits,
				sge::systems::detail::extract_parameter_type<
					boost::mpl::_1
				>
			>
		>::type::value
	));

	return
		result;
}

}
}
}

#endif
