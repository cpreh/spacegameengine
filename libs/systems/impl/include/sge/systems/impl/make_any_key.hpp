//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_MAKE_ANY_KEY_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_MAKE_ANY_KEY_HPP_INCLUDED

#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/any_key_fwd.hpp>


namespace sge::systems::impl
{

sge::systems::detail::any_key
make_any_key(
	sge::systems::detail::any const &
);

}

#endif
