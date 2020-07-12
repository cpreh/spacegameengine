//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_ANY_MAP_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_ANY_MAP_HPP_INCLUDED

#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/any_key.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

using
any_map
=
std::map<
	sge::systems::detail::any_key,
	sge::systems::detail::any
>;

}
}
}

#endif
