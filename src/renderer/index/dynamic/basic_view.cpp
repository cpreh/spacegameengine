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


#include <sge/renderer/index/dynamic/basic_view.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/size_type.hpp>
#include <fcppt/export_symbol.hpp>

template<
	bool IsConst
>
sge::renderer::index::dynamic::basic_view<IsConst>::basic_view(
	pointer const _data,
	size_type const _size,
	dynamic::format::type const _format
)
:
	data_(_data),
	size_(_size),
	format_(_format)
{}
	
template<
	bool IsConst
>
typename sge::renderer::index::dynamic::basic_view<IsConst>::pointer
sge::renderer::index::dynamic::basic_view<IsConst>::data() const
{
	return data_;
}

template<
	bool IsConst
>
sge::renderer::size_type
sge::renderer::index::dynamic::basic_view<IsConst>::size() const
{
	return size_;
}

template<
	bool IsConst
>
sge::renderer::index::dynamic::format::type
sge::renderer::index::dynamic::basic_view<IsConst>::format() const
{
	return format_;
}

#define SGE_RENDERER_INDEX_DYNAMIC_DEFINE_BASIC_VIEW(x)\
template FCPPT_EXPORT_SYMBOL \
class sge::renderer::index::dynamic::basic_view<\
	x\
>;

SGE_RENDERER_INDEX_DYNAMIC_DEFINE_BASIC_VIEW(true)
SGE_RENDERER_INDEX_DYNAMIC_DEFINE_BASIC_VIEW(false)

#undef SGE_RENDERER_INDEX_DYNAMIC_DEFINE_BASIC_VIEW
