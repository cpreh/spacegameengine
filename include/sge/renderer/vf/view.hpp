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


#ifndef SGE_RENDERER_VF_VIEW_HPP_INCLUDED
#define SGE_RENDERER_VF_VIEW_HPP_INCLUDED

#include <sge/renderer/vf/view_fwd.hpp>
#include <sge/renderer/vf/dynamic/view.hpp>
#include <sge/renderer/vf/iterator_fwd.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename VertexFormat
>
class view
{
	FCPPT_NONASSIGNABLE(
		view
	)
public:
	typedef vf::iterator<
		VertexFormat
	> iterator;

	typedef typename VertexFormat::pointer pointer;

	typedef dynamic::basic_view<
		pointer
	> dynamic_view_type;

	typedef vertex_size size_type;

	explicit view(
		dynamic_view_type const &_view
	)
	:
		data_(
			_view.data()
		),
		size_(
			_view.size()
		)
	{}

	template<
		typename OtherView
	>
	explicit view(
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
	{}

	iterator
	begin() const
	{
		return
			iterator(
				data_
			);
	}

	iterator
	end() const
	{
		return
			iterator(
				data_
				+ size_
			);
	}
private:
	pointer const data_;

	size_type const size_;
};

}
}
}

#endif
