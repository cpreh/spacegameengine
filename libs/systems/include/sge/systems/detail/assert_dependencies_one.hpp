//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_ASSERT_DEPENDENCIES_ONE_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_ASSERT_DEPENDENCIES_ONE_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

template<
	typename Choices,
	typename Option
>
using
assert_dependencies_one
=
metal::all_of<
	typename
	Option::needs_before,
	metal::bind<
		metal::lambda<
			metal::contains
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
