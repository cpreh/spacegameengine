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


#ifndef SGE_IMAGE_IMPL_VIEW_SUB_ANY_HPP_INCLUDED
#define SGE_IMAGE_IMPL_VIEW_SUB_ANY_HPP_INCLUDED

#include <sge/image/box.hpp>
#include <sge/image/mizuiro_color.hpp>
#include <sge/image/impl/to_mizuiro_dim.hpp>
#include <sge/image/view/wrap.hpp>
#include <mizuiro/image/sub_view.hpp>
#include <fcppt/math/vector/to_dim.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace impl
{
namespace view
{

template<
	typename View,
	typename Box
>
View
sub_any(
	View const &_view,
	Box const &_box
)
{
	return
		fcppt::variant::apply_unary(
			[
				&_box
			](
				auto const &_src
			)
			{
				typedef
				typename
				std::decay<
					decltype(
						_src
					)
				>::type
				source_type;

				return
					View(
						sge::image::view::wrap(
							mizuiro::image::sub_view(
								_src,
								typename
								source_type::bound_type{
									sge::image::impl::to_mizuiro_dim(
										fcppt::math::vector::to_dim(
											_box.pos()
										)
									),
									sge::image::impl::to_mizuiro_dim(
										_box.size()
									)
								}
							)
						)
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
