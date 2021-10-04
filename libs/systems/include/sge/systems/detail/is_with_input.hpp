//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_IS_WITH_INPUT_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_IS_WITH_INPUT_HPP_INCLUDED

#include <sge/systems/with_input_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::systems::detail
{

template<
	typename Type
>
struct is_with_input
:
std::false_type
{
};

template<>
struct is_with_input<
	sge::systems::with_input
>
:
std::true_type
{
};

}

#endif
