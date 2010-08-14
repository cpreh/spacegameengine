/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_STATE_VAR_IMPL_HPP_INCLUDED
#define SGE_RENDERER_STATE_VAR_IMPL_HPP_INCLUDED

#include <sge/renderer/state/var.hpp>

template<
	typename T,
	typename States
>
sge::renderer::state::var<T, States> &
sge::renderer::state::var<T, States>::operator=(
	value_type const &newval)
{
	val_ = newval;
	return *this;
}

template<
	typename T,
	typename States
>
typename sge::renderer::state::var<T, States>::state_type
sge::renderer::state::var<T, States>::state() const
{
	return state_;
}

template<
	typename T,
	typename States
>
T
sge::renderer::state::var<T, States>::value() const
{
	return val_;
}

template<
	typename T,
	typename States
>
sge::renderer::state::var<T, States>::var(
	state_type const state_,
	value_type const &val_)
:
	state_(state_),
	val_(val_)
{}

#endif
