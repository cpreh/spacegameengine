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


#include <sge/renderer/index/view_operations.hpp>

template<
	typename T
>
sge::renderer::size_type
sge::renderer::index::view_size::operator()(
	T const &src) const
{
	return src.size();
}

template<
	typename T
>
sge::renderer::size_type
sge::renderer::index::view_stride::operator()(
	T const &) const
{
	return sizeof(typename T::value_type);
}

template<
	typename T
>
sge::renderer::index::format::type
sge::renderer::index::view_format::operator()(
	T const &src) const
{
	return src.format();
}

#define SGE_INSTANTIATE_INDEX_VIEW_SIZE(x) \
template sge::renderer::size_type \
sge::renderer::index::view_size::operator()( \
	sge::renderer::index::x const &) const;

SGE_INSTANTIATE_INDEX_VIEW_SIZE(view_16)
SGE_INSTANTIATE_INDEX_VIEW_SIZE(view_32)
SGE_INSTANTIATE_INDEX_VIEW_SIZE(const_view_16)
SGE_INSTANTIATE_INDEX_VIEW_SIZE(const_view_32)

#undef SGE_INSTANTIATE_INDEX_VIEW_SIZE


#define SGE_INSTANTIATE_INDEX_VIEW_STRIDE(x) \
template sge::renderer::size_type \
sge::renderer::index::view_stride::operator()( \
	sge::renderer::index::x const &) const;

SGE_INSTANTIATE_INDEX_VIEW_STRIDE(view_16)
SGE_INSTANTIATE_INDEX_VIEW_STRIDE(view_32)
SGE_INSTANTIATE_INDEX_VIEW_STRIDE(const_view_16)
SGE_INSTANTIATE_INDEX_VIEW_STRIDE(const_view_32)

#undef SGE_INSTANTIATE_INDEX_VIEW_STRIDE


#define SGE_INSTANTIATE_INDEX_VIEW_FORMAT(x) \
template sge::renderer::index::format::type \
sge::renderer::index::view_format::operator()( \
	sge::renderer::index::x const &) const;

SGE_INSTANTIATE_INDEX_VIEW_FORMAT(view_16)
SGE_INSTANTIATE_INDEX_VIEW_FORMAT(view_32)
SGE_INSTANTIATE_INDEX_VIEW_FORMAT(const_view_16)
SGE_INSTANTIATE_INDEX_VIEW_FORMAT(const_view_32)

#undef SGE_INSTANTIATE_INDEX_VIEW_FORMAT
