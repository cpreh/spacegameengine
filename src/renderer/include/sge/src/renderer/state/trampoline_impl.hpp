/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_RENDERER_STATE_TRAMPOLINE_IMPL_HPP_INCLUDED
#define SGE_SRC_RENDERER_STATE_TRAMPOLINE_IMPL_HPP_INCLUDED

#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


template<
	typename T,
	typename States
>
sge::renderer::state::trampoline<T, States>::trampoline(
	state_type const _state
)
:
	state_(_state)
{
}

template<
	typename T,
	typename States
>
sge::renderer::state::trampoline<T, States>::~trampoline()
{
}

template<
	typename T,
	typename States
>
typename sge::renderer::state::trampoline<T, States>::var_type const
sge::renderer::state::trampoline<T, States>::operator=(
	T const &_value
) const
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)
	return
		var_type(
			state_,
			_value
		);
FCPPT_PP_POP_WARNING
}

template<
	typename T,
	typename States
>
typename sge::renderer::state::trampoline<T, States>::state_type
sge::renderer::state::trampoline<T, States>::state() const
{
	return state_;
}

#endif
