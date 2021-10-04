//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_ANY_LIST_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_ANY_LIST_HPP_INCLUDED

#include <sge/systems/detail/any.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::systems::detail
{

using
any_list
=
std::vector<
	sge::systems::detail::any
>;

}

#endif
