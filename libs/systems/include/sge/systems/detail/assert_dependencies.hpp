//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_ASSERT_DEPENDENCIES_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_ASSERT_DEPENDENCIES_HPP_INCLUDED

#include <sge/systems/detail/assert_dependencies_one.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/lambda/always.hpp>
#include <metal/lambda/arg.hpp>
#include <metal/lambda/bind.hpp>
#include <metal/lambda/lambda.hpp>
#include <metal/list/all_of.hpp>
#include <fcppt/config/external_end.hpp>


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
metal::all_of<
	Choices,
	metal::bind<
		metal::lambda<
			sge::systems::detail::assert_dependencies_one
		>,
		metal::always<
			Choices
		>,
		metal::_1
	>
>;

}
}
}

#endif
