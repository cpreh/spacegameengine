/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENGL_STATE_SET_OR_DEFAULT_SINGLE_HPP_INCLUDED
#define SGE_OPENGL_STATE_SET_OR_DEFAULT_SINGLE_HPP_INCLUDED

#include <fcppt/make_cref.hpp>
#include <fcppt/reference_wrapper_impl.hpp>
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
			fcppt::reference_wrapper<
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
