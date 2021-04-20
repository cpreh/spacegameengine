//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_UNPACK_IF_PRESENT_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_UNPACK_IF_PRESENT_HPP_INCLUDED

#include <sge/systems/detail/any.hpp>
#include <sge/systems/detail/any_key.hpp>
#include <sge/systems/detail/any_map.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/to_optional.hpp>


namespace sge
{
namespace systems
{
namespace impl
{

template<
	typename Parameter,
	typename Function
>
void
unpack_if_present(
	sge::systems::detail::any_map const &_map,
	sge::systems::detail::any_key const _key,
	Function const _function
)
{
	fcppt::optional::maybe_void(
		fcppt::container::find_opt_mapped(
			_map,
			_key
		),
		[
			_function
		](
			fcppt::reference<
				sge::systems::detail::any const
			> const _element
		)
		{
			_function(
				FCPPT_ASSERT_OPTIONAL_ERROR(
					fcppt::variant::to_optional<
						Parameter
					>(
						_element.get()
					)
				)
			);
		}
	);
}
}

}
}

#endif
