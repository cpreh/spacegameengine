//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_MAKE_DEFAULT_ELEMENT_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_MAKE_DEFAULT_ELEMENT_HPP_INCLUDED

#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/extract_parameter_type.hpp>
#include <fcppt/tag.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

template<
	typename Type
>
inline
sge::systems::detail::any
make_default_element(
	fcppt::tag<
		Type
	>
)
{
	return
		sge::systems::detail::any{
			sge::systems::detail::extract_parameter_type<
				Type
			>{}
		};
}

}
}
}

#endif
