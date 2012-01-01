/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_VF_VIEW_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_VIEW_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/iterator_impl.hpp>
#include <sge/renderer/vf/view_decl.hpp>
#include <sge/renderer/vf/dynamic/basic_view.hpp>


template<
	typename Part,
	typename Constness
>
sge::renderer::vf::view<Part, Constness>::view(
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
}

template<
	typename Part,
	typename Constness
>
template<
	typename OtherView
>
sge::renderer::vf::view<Part, Constness>::view(
	dynamic::basic_view<
		OtherView
	> const &_view
)
:
	data_(
		_view.data()
	),
	size_(
		_view.size()
	)
{
}

template<
	typename Part,
	typename Constness
>
typename sge::renderer::vf::view<Part, Constness>::iterator
sge::renderer::vf::view<Part, Constness>::begin() const
{
	return
		iterator(
			data_
		);
}

template<
	typename Part,
	typename Constness
>
typename sge::renderer::vf::view<Part, Constness>::iterator
sge::renderer::vf::view<Part, Constness>::end() const
{
	return
		iterator(
			data_
			+ size_.get()
		);
}

#endif
