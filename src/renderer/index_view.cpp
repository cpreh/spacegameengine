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


#include <sge/renderer/index_view.hpp>

template<typename Index>
sge::renderer::index_view<Index>::index_view(
	pointer const data_,
	size_type const size_)
: data_(data_),
  size_(size_)
{}

template<typename Index>
typename sge::renderer::index_view<Index>::pointer
sge::renderer::index_view<Index>::data() const
{
	return data_;
}

template<typename Index>
typename sge::renderer::index_view<Index>::size_type
sge::renderer::index_view<Index>::size() const
{
	return size_;
}

template<typename Index>
typename sge::renderer::index_view<Index>::iterator
sge::renderer::index_view<Index>::begin() const
{
	return data();
}

template<typename Index>
typename sge::renderer::index_view<Index>::iterator
sge::renderer::index_view<Index>::end() const
{
	return begin() + size();
}

template<typename Index>
sge::renderer::index_format::type
sge::renderer::index_view<Index>::format() const
{
	//return index_format_from_stride(
	//	stride());
}

template class sge::renderer::index_view<sge::uint16>;
template class sge::renderer::index_view<sge::uint32>;
template class sge::renderer::index_view<sge::uint16 const>;
template class sge::renderer::index_view<sge::uint32 const>;
