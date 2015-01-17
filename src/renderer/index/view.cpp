/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/size_type.hpp>
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/dynamic/basic_view.hpp>
#include <sge/renderer/index/dynamic/make_format.hpp>
#include <sge/src/core/export_class_instantiation.hpp>
#include <sge/src/renderer/index/instantiate_all.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/cast/to_signed.hpp>


template<
	typename Format
>
sge::renderer::index::view<
	Format
>::view(
	pointer const _data,
	size_type const _size
)
:
	data_(
		_data
	),
	size_(
		_size
	)
{
	FCPPT_ASSERT_PRE(
		data_
	);
}

template<
	typename Format
>
sge::renderer::index::view<
	Format
>::view(
	nonconst_type const &_other
)
:
	data_(
		_other.data()
	),
	size_(
		_other.size()
	)
{
}

template<
	typename Format
>
sge::renderer::index::view<
	Format
>::view(
	dynamic_view_type const &_view
)
:
	data_(
		_view.data()
	),
	size_(
		_view.size()
	)
{
	FCPPT_ASSERT_PRE(
		_view.format()
		==
		sge::renderer::index::dynamic::make_format<
			Format
		>()
	);
}

template<
	typename Format
>
typename sge::renderer::index::view<
	Format
>::pointer
sge::renderer::index::view<
	Format
>::data() const
{
	return data_;
}

template<
	typename Format
>
sge::renderer::size_type
sge::renderer::index::view<
	Format
>::size() const
{
	return size_;
}

template<
	typename Format
>
typename sge::renderer::index::view<
	Format
>::iterator
sge::renderer::index::view<
	Format
>::begin() const
{
	return
		iterator(
			this->data()
		);
}

template<
	typename Format
>
typename sge::renderer::index::view<
	Format
>::iterator
sge::renderer::index::view<
	Format
>::end() const
{
	return
		iterator(
			this->begin()
			+
			fcppt::cast::to_signed(
				this->size()
			)
		);
}

#define SGE_RENDERER_INDEX_DEFINE_VIEW(\
	format\
)\
template \
class \
SGE_CORE_EXPORT_CLASS_INSTANTIATION \
sge::renderer::index::view<\
	format \
>

SGE_RENDERER_INDEX_INSTANTIATE_ALL(
	SGE_RENDERER_INDEX_DEFINE_VIEW
);

#undef SGE_RENDERER_INDEX_DEFINE_VIEW
