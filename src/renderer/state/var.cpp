/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/types.hpp>

template<typename T>
sge::renderer::state::var<T> &
sge::renderer::state::var<T>::operator=(
	value_type const newval)
{
	val_ = newval;
	return *this;
}

template<typename T>
typename sge::renderer::state::var<T>::state_type
sge::renderer::state::var<T>::state() const
{
	return state_;
}

template<typename T>
T sge::renderer::state::var<T>::value() const
{
	return val_;
}

template<typename T>
sge::renderer::state::var<T>::var(
	state_type const state_,
	value_type const val_)
:
	state_(state_),
	val_(val_)
{}

template class sge::renderer::state::var<sge::renderer::state::int_type>;
template class sge::renderer::state::var<sge::renderer::state::uint_type>;
template class sge::renderer::state::var<sge::renderer::state::float_type>;
template class sge::renderer::state::var<sge::renderer::state::bool_type>;
template class sge::renderer::state::var<sge::renderer::state::color_type>;
