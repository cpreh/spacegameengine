//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_LIST_IMPL_HPP_INCLUDED
#define SGE_SYSTEMS_LIST_IMPL_HPP_INCLUDED

#include <sge/systems/list_decl.hpp>
#include <fcppt/container/tuple/push_back.hpp>
#include <fcppt/container/tuple/push_back_result.hpp>


template<
	typename Inits
>
sge::systems::list<
	Inits
>::list(
	Inits const &_inits
)
:
	inits_{
		_inits
	}
{
}

template<
	typename Inits
>
template<
	typename Param
>
sge::systems::list<
	fcppt::container::tuple::push_back_result<
		Inits,
		Param
	>
>
sge::systems::list<
	Inits
>::operator()(
	Param const &_param
) const
{
	return
		sge::systems::list<
			fcppt::container::tuple::push_back_result<
				Inits,
				Param
			>
		>(
			fcppt::container::tuple::push_back(
				inits_,
				_param
			)
		);
}

template<
	typename Inits
>
Inits const &
sge::systems::list<
	Inits
>::get() const
{
	return
		inits_;
}

#endif
