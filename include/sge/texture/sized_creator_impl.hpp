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


#ifndef SGE_TEXTURE_SIZED_CREATOR_IMPL_HPP_INCLUDED
#define SGE_TEXTURE_SIZED_CREATOR_IMPL_HPP_INCLUDED

#include "sized_creator.hpp"
#include "../renderer/device.hpp"

template<typename T>
sge::texture::sized_creator<T>::sized_creator(
	renderer::device_ptr const rend,
	renderer::filter_args const &filter,
	renderer::texture::dim_type const &dim)
:
	rend(rend),
	filter(filter),
	dim(dim)
{}

template<typename T>
sge::texture::fragmented_auto_ptr
sge::texture::sized_creator<T>::operator()() const
{
	return fragmented_auto_ptr(
		new T(
			rend,
			filter,
			dim));
}

#endif
