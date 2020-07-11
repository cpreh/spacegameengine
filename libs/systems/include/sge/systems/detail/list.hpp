//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_LIST_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_LIST_HPP_INCLUDED

#include <sge/systems/detail/any_list.hpp>
#include <sge/systems/detail/any_map.hpp>
#include <sge/systems/detail/list_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

class list
{
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	explicit
	list(
		sge::systems::detail::any_list const &
	);

	[[nodiscard]]
	sge::systems::detail::any_map const &
	get() const;
private:
	sge::systems::detail::any_map states_;
};

}
}
}

#endif
