//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_MAKE_LIST_ELEMENT_IMPL_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_MAKE_LIST_ELEMENT_IMPL_HPP_INCLUDED

#include <sge/systems/renderer.hpp>
#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/renderer.hpp>
#include <sge/systems/detail/renderer_caps.hpp>


namespace sge
{
namespace systems
{
namespace detail
{


template<
	typename Choices,
	typename Type
>
sge::systems::detail::any
make_list_element_impl(
	Type const &_type
)
{
	return
		sge::systems::detail::any{
			_type
		};
}

template<
	typename Choices
>
inline
sge::systems::detail::any
make_list_element_impl(
	sge::systems::renderer const &_renderer
)
{
	return
		sge::systems::detail::any{
			sge::systems::detail::renderer{
				_renderer,
				sge::systems::detail::renderer_caps<
					Choices
				>::value
			}
		};
}

}
}
}

#endif
