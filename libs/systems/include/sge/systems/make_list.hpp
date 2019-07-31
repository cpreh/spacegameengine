//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_MAKE_LIST_HPP_INCLUDED
#define SGE_SYSTEMS_MAKE_LIST_HPP_INCLUDED

#include <sge/systems/list_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

template<
	typename Param
>
inline
sge::systems::list<
	std::tuple<
		Param
	>
>
make_list(
	Param const &_param
)
{
	return
		sge::systems::list<
			std::tuple<
				Param
			>
		>{
			std::tuple<
				Param
			>{
				_param
			}
		};
}

}
}

#endif
