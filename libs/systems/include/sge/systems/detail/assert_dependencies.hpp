//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_ASSERT_DEPENDENCIES_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_ASSERT_DEPENDENCIES_HPP_INCLUDED

#include <sge/systems/detail/assert_dependencies_one.hpp>
#include <fcppt/mpl/arg.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/all_of.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

template<
	typename Choices
>
using
assert_dependencies
=
fcppt::mpl::list::all_of<
	Choices,
	fcppt::mpl::bind<
		fcppt::mpl::lambda<
			sge::systems::detail::assert_dependencies_one
		>,
		fcppt::mpl::constant<
			Choices
		>,
		fcppt::mpl::arg<1>
	>
>;

}
}
}

#endif
