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


#include "instantiate_all.hpp"
#include <sge/renderer/index/iterator.hpp>
#include <sge/renderer/index/const_proxy.hpp>
#include <sge/renderer/index/proxy.hpp>

template<
	typename Format
>
sge::renderer::index::iterator<Format>::iterator(
	pointer const _data
)
:
	data_(_data)
{
}

template<
	typename Format
>
sge::renderer::index::iterator<Format>::iterator(
	nonconst_iterator const &_other
)
:
	data_(_other.data())
{
}

template<
	typename Format
>
typename sge::renderer::index::iterator<Format>::pointer
sge::renderer::index::iterator<Format>::data() const
{
	return data_;
}

template<
	typename Format
>
void
sge::renderer::index::iterator<Format>::advance(
	difference_type const _diff
)
{
	data_ +=
		_diff
		* static_cast<
			difference_type
		>(
			sizeof(
				value_type
			)
		);
}

template<
	typename Format
>
void
sge::renderer::index::iterator<Format>::increment()
{
	this->advance(
		1
	);
}

template<
	typename Format
>
void
sge::renderer::index::iterator<Format>::decrement()
{
	this->advance(
		-1
	);
}

template<
	typename Format
>
bool
sge::renderer::index::iterator<Format>::equal(
	iterator const &_other
) const
{
	return
		data_
		== _other.data_;
}

template<
	typename Format
>
typename sge::renderer::index::iterator<Format>::difference_type
sge::renderer::index::iterator<Format>::distance_to(
	iterator const &_other
) const
{
	return
		(
			_other.data_
			- data_
		)
		/
		static_cast<
			difference_type
		>(
			sizeof(value_type)
		);
}

template<
	typename Format
>
typename sge::renderer::index::iterator<Format>::reference
sge::renderer::index::iterator<Format>::dereference() const
{
	return
		reference(
			data_
		);
}

#define SGE_RENDERER_INDEX_DEFINE_ITERATOR(\
	format\
)\
template FCPPT_EXPORT_SYMBOL \
class sge::renderer::index::iterator<\
	format \
>;

SGE_RENDERER_INDEX_INSTANTIATE_ALL(
	SGE_RENDERER_INDEX_DEFINE_ITERATOR
)

#undef SGE_RENDERER_INDEX_DEFINE_ITERATOR
