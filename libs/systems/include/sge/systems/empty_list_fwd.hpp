//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_EMPTY_LIST_FWD_HPP_INCLUDED
#define SGE_SYSTEMS_EMPTY_LIST_FWD_HPP_INCLUDED

#include <sge/systems/list_fwd.hpp>
#include <fcppt/tuple/object_fwd.hpp>


namespace sge::systems
{

using
empty_list
=
sge::systems::list<
	fcppt::tuple::object<>
>;

}

#endif
