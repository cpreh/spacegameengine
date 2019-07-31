//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_ASSERT_DEPENDENCIES_ONE_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_ASSERT_DEPENDENCIES_ONE_HPP_INCLUDED

#include <fcppt/brigand/all_of.hpp>
#include <fcppt/brigand/found_t.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/types/args.hpp>
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
fcppt::brigand::all_of<
	typename
	Option::needs_before,
	brigand::bind<
		fcppt::brigand::found_t,
		brigand::pin<
			Choices
		>,
		brigand::_1
	>
>;

}
}
}

#endif
