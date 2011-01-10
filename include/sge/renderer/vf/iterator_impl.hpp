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


#ifndef SGE_RENDERER_VF_ITERATOR_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_ITERATOR_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/iterator_decl.hpp>
#include <boost/mpl/back.hpp>

template<
	typename VertexFormat
>
typename sge::renderer::vf::iterator<VertexFormat>::difference_type
sge::renderer::vf::iterator<VertexFormat>::stride()
{
	return
		static_cast<
			difference_type
		>(
			boost::mpl::back<
				typename VertexFormat::offsets
			>::type::value
		);
}

template<
	typename VertexFormat
>
sge::renderer::vf::iterator<VertexFormat>::iterator(
	internal_pointer const _data
)
:
	data_(_data)
{}

template<
	typename VertexFormat
>
void
sge::renderer::vf::iterator<VertexFormat>::advance(
	difference_type const _diff
)
{
	data_ += stride() * _diff;
}

template<
	typename VertexFormat
>
void
sge::renderer::vf::iterator<VertexFormat>::increment()
{
	data_ += stride();
}

template<
	typename VertexFormat
>
void
sge::renderer::vf::iterator<VertexFormat>::decrement()
{
	data_ -= stride();
}

template<
	typename VertexFormat
>
bool
sge::renderer::vf::iterator<VertexFormat>::equal(
	iterator const &_other
) const
{
	return data_ == _other.data_;
}

template<
	typename VertexFormat
>
typename sge::renderer::vf::iterator<VertexFormat>::difference_type
sge::renderer::vf::iterator<VertexFormat>::distance_to(
	iterator const &_other
) const
{
	return
		(_other.data_ - data_)
		/
		stride();
}

template<
	typename VertexFormat
>
typename sge::renderer::vf::iterator<VertexFormat>::vertex_type
sge::renderer::vf::iterator<VertexFormat>::dereference() const
{
	return
		vertex_type(
			data_
		);
}

#endif
