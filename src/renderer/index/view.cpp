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


#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <sge/renderer/index/dynamic/basic_view.hpp>
#include <sge/renderer/index/format.hpp>
#include <sge/renderer/index/i16.hpp>
#include <sge/renderer/index/i32.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/variant/object_impl.hpp>

template<
	typename Format
>
sge::renderer::index::view<Format>::view(
	pointer const _data,
	size_type const _size
)
:
	data_(_data),
	size_(_size)
{
	FCPPT_ASSERT(data_);
}

template<
	typename Format
>
sge::renderer::index::view<Format>::view(
	nonconst_type const &_other
)
:
	data_(_other.data()),
	size_(_other.size())
{
}

template<
	typename Format
>
sge::renderer::index::view<Format>::view(
	dynamic_view_type const &_view
)
:
	data_(
		_view.any(). template get<
			view<
				Format
			>
		>().data()
	),
	size_(
		_view.size()
	)
{}

template<
	typename Format
>
typename sge::renderer::index::view<Format>::pointer
sge::renderer::index::view<Format>::data() const
{
	return data_;
}

template<
	typename Format
>
sge::renderer::size_type
sge::renderer::index::view<Format>::size() const
{
	return size_;
}

template<
	typename Format
>
typename sge::renderer::index::view<Format>::iterator
sge::renderer::index::view<Format>::begin() const
{
	return data();
}

template<
	typename Format
>
typename sge::renderer::index::view<Format>::iterator
sge::renderer::index::view<Format>::end() const
{
	return begin() + size();
}

template<
	typename Format
>
sge::renderer::index::dynamic::format::type
sge::renderer::index::view<Format>::format() const
{
	return
		dynamic::make_format<
			Format
		>();
}

#define SGE_RENDERER_INDEX_DEFINE_VIEW(x)\
template FCPPT_EXPORT_SYMBOL class sge::renderer::index::view<\
	sge::renderer::index::format<\
		x\
	> \
>;

SGE_RENDERER_INDEX_DEFINE_VIEW(
	sge::renderer::index::i16
)

SGE_RENDERER_INDEX_DEFINE_VIEW(
	sge::renderer::index::i16 const
)

SGE_RENDERER_INDEX_DEFINE_VIEW(
	sge::renderer::index::i32
)

SGE_RENDERER_INDEX_DEFINE_VIEW(
	sge::renderer::index::i32 const
)

#undef SGE_RENDERER_INDEX_DEFINE_VIEW
