//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_STATE_SET_OR_DEFAULT_HPP_INCLUDED
#define SGE_D3D9_STATE_SET_OR_DEFAULT_HPP_INCLUDED

#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{

template<
	typename State,
	typename D3DState
>
void
set_or_default(
	fcppt::optional::reference<
		State const
	> const _state_ref,
	D3DState const &_default_state
)
{
	fcppt::optional::maybe(
		_state_ref,
		[
			&_default_state
		]()
		{
			return
				fcppt::make_cref(
					_default_state
				);
		},
		[](
			fcppt::reference<
				State const
			> const _ref
		)
		{
			return
				fcppt::make_cref(
					fcppt::cast::static_downcast<
						D3DState const &
					>(
						_ref.get()
					)
				);
		}
	).get().set();
}

}
}
}

#endif
