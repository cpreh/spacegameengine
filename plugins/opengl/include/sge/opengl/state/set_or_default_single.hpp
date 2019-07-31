//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_SET_OR_DEFAULT_SINGLE_HPP_INCLUDED
#define SGE_OPENGL_STATE_SET_OR_DEFAULT_SINGLE_HPP_INCLUDED

#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace opengl
{
namespace state
{

template<
	typename GLState,
	typename Context,
	typename State
>
void
set_or_default_single(
	Context const &_context,
	fcppt::optional::reference<
		State const
	> const _state
)
{
	fcppt::optional::maybe(
		_state,
		[
			&_context
		]()
		{
			return
				fcppt::make_cref(
					_context.default_state()
				);
		},
		[](
			fcppt::reference<
				State const
			> const _value
		)
		{
			return
				fcppt::make_cref(
					fcppt::cast::static_downcast<
						GLState const &
					>(
						_value.get()
					)
				);
		}
	).get().set();
}

}
}
}

#endif
