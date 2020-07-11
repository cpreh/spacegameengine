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
#include <fcppt/type_traits/remove_cv_ref_t.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>


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
std::enable_if_t<
	std::negation_v<
		std::is_same<
			fcppt::type_traits::remove_cv_ref_t<
				Type
			>,
			sge::systems::renderer
		>
	>,
	sge::systems::detail::any
>
make_list_element_impl(
	Type &&_value
)
{
	return
		sge::systems::detail::any{
			std::forward<
				Type
			>(
				_value
			)
		};
}

template<
	typename Choices,
	typename Type
>
inline
std::enable_if_t<
	std::is_same_v<
		fcppt::type_traits::remove_cv_ref_t<
			Type
		>,
		sge::systems::renderer
	>,
	sge::systems::detail::any
>
make_list_element_impl(
	Type &&_value
)
{
	return
		sge::systems::detail::any{
			sge::systems::detail::renderer{
				std::forward<
					Type
				>(
					_value
				),
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
