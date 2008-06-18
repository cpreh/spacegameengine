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


#include <sge/renderer/index_view_operations.hpp>

template<typename T>
sge::renderer::index_view_size::size_type
sge::renderer::index_view_size::operator()(
	T const &src) const
{
	return src.size();
}

template<typename T>
sge::renderer::index_view_stride::size_type
sge::renderer::index_view_stride::operator()(
	T const &) const
{
	return sizeof(typename T::value_type);
}


template<typename T>
unsigned char const *
sge::renderer::index_view_data::operator()(
	T const &src) const
{
	return reinterpret_cast<unsigned char const *>(src.data());
}


#define SGE_INSTANTIATE_INDEX_VIEW_SIZE(x) \
template sge::renderer::index_view_size::size_type \
sge::renderer::index_view_size::operator()( \
	sge::renderer::x const &) const;

SGE_INSTANTIATE_INDEX_VIEW_SIZE(index_view_16)
SGE_INSTANTIATE_INDEX_VIEW_SIZE(index_view_32)
SGE_INSTANTIATE_INDEX_VIEW_SIZE(const_index_view_16)
SGE_INSTANTIATE_INDEX_VIEW_SIZE(const_index_view_32)

#undef SGE_INSTANTIATE_INDEX_VIEW_SIZE


#define SGE_INSTANTIATE_INDEX_VIEW_STRIDE(x) \
template sge::renderer::index_view_stride::size_type \
sge::renderer::index_view_stride::operator()( \
	sge::renderer::x const &) const;

SGE_INSTANTIATE_INDEX_VIEW_STRIDE(index_view_16)
SGE_INSTANTIATE_INDEX_VIEW_STRIDE(index_view_32)
SGE_INSTANTIATE_INDEX_VIEW_STRIDE(const_index_view_16)
SGE_INSTANTIATE_INDEX_VIEW_STRIDE(const_index_view_32)

#undef SGE_INSTANTIATE_INDEX_VIEW_STRIDE


#define SGE_INSTANTIATE_INDEX_VIEW_DATA(x) \
template unsigned char const * \
sge::renderer::index_view_data::operator()( \
	sge::renderer::x const &) const;

SGE_INSTANTIATE_INDEX_VIEW_DATA(index_view_16)
SGE_INSTANTIATE_INDEX_VIEW_DATA(index_view_32)
SGE_INSTANTIATE_INDEX_VIEW_DATA(const_index_view_16)
SGE_INSTANTIATE_INDEX_VIEW_DATA(const_index_view_32)

#undef SGE_INSTANTIATE_INDEX_VIEW_STRIDE
