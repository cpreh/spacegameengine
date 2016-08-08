/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_IMAGE_IMPL_VIEW_SIZE_ANY_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_SIZE_ANY_HPP_INCLUDED

#include <sge/image/impl/from_mizuiro_dim.hpp>
#include <sge/image/traits/dim_fwd.hpp>
#include <fcppt/variant/apply_unary.hpp>


namespace sge
{
namespace image
{
namespace impl
{
namespace view
{

template<
	typename Tag,
	typename View
>
typename
sge::image::traits::dim<
	Tag
>::type
size_any(
	View const &_view
)
{
	return
		fcppt::variant::apply_unary(
			[](
				auto const &_src
			)
			{
				return
					sge::image::impl::from_mizuiro_dim(
						_src.size()
					);
			},
			_view.get()
		);
}

}
}
}
}

#endif
