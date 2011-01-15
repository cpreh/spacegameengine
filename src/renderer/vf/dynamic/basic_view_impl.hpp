/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_VF_DYNAMIC_BASIC_VIEW_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_BASIC_VIEW_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/basic_view.hpp>

template<
	typename Pointer
>
sge::renderer::vf::dynamic::basic_view<Pointer>::basic_view(
	pointer const _data,
	size_type const _size,
	dynamic::format const &_format
)
:
	data_(_data),
	size_(_size),
	format_(_format)
{}

template<
	typename Pointer
>
typename sge::renderer::vf::dynamic::basic_view<Pointer>::pointer
sge::renderer::vf::dynamic::basic_view<Pointer>::data() const
{
	return data_;
}

template<
	typename Pointer
>
typename sge::renderer::vf::dynamic::basic_view<Pointer>::size_type
sge::renderer::vf::dynamic::basic_view<Pointer>::size() const
{
	return size_;
}

template<
	typename Pointer
>
sge::renderer::vf::dynamic::format const &
sge::renderer::vf::dynamic::basic_view<Pointer>::format() const
{
	return format_;
}

#endif
