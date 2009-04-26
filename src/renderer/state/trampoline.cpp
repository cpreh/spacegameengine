/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#include <sge/renderer/state/trampoline.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/types.hpp>

template<typename T>
sge::renderer::state::trampoline<T>::trampoline(
	state_type const state_)
:
	state_(state_)
{}

template<typename T>
typename sge::renderer::state::trampoline<T>::var_type const
sge::renderer::state::trampoline<T>::operator=(
	T const t) const
{
	return var<T>(
		state_,
		t);
}

template<typename T>
typename sge::renderer::state::trampoline<T>::state_type
sge::renderer::state::trampoline<T>::state() const
{
	return state_;
}

template class sge::renderer::state::trampoline<sge::renderer::state::int_type>;
template class sge::renderer::state::trampoline<sge::renderer::state::uint_type>;
template class sge::renderer::state::trampoline<sge::renderer::state::float_type>;
template class sge::renderer::state::trampoline<sge::renderer::state::bool_type>;
template class sge::renderer::state::trampoline<sge::renderer::state::color_type>;
