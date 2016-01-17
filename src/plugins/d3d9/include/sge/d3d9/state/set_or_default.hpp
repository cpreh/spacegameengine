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
