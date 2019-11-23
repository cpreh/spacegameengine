//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_DETAIL_MAKE_LIST_ELEMENT_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_MAKE_LIST_ELEMENT_HPP_INCLUDED

#include <sge/systems/config_fwd.hpp>
#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/extract_parameter_type.hpp>
#include <sge/systems/detail/make_list_element_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/lambda/always.hpp>
#include <metal/lambda/bind.hpp>
#include <metal/lambda/lambda.hpp>
#include <metal/lambda/trait.hpp>
#include <metal/list/any_of.hpp>
#include <type_traits>
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
inline
sge::systems::detail::any
make_list_element(
	Type const &_type
)
{
	// Check that the given parameter is actually part of the
	// static subsystems
	static_assert(
		std::is_same<
			Type,
			sge::systems::config
		>::value
		||
		metal::any_of<
			Choices,
			metal::bind<
				metal::trait<
					std::is_same
				>,
				metal::always<
					Type
				>,
				metal::lambda<
					sge::systems::detail::extract_parameter_type
				>
			>
		>::value,
		"Parameter given to sge::systems::list is not part of the system choices"
	);

	return
		sge::systems::detail::make_list_element_impl<
			Choices
		>(
			_type
		);
}

}
}
}

#endif
