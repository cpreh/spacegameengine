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


#ifndef SGE_IMAGE_STORE_ELEMENTS_HPP_INCLUDED
#define SGE_IMAGE_STORE_ELEMENTS_HPP_INCLUDED

#include <sge/image/store/basic.hpp>
#include <sge/image/traits/image/color_tag.hpp>
#include <sge/image/traits/image/dimension.hpp>
#include <sge/image/traits/pixel/static_formats.hpp>
#include <sge/image/view/basic_format_c.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/transform.hpp>
#include <brigand/functions/lambda/apply.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/types/args.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace store
{

template<
	typename Tag
>
using
elements
=
brigand::transform<
	sge::image::traits::pixel::static_formats<
		sge::image::traits::image::color_tag<
			Tag
		>
	>,
	brigand::bind<
		sge::image::store::basic,
		brigand::bind<
			sge::image::view::basic_format_c,
			brigand::pin<
				sge::image::traits::image::dimension<
					Tag
				>
			>,
			brigand::_1
		>
	>
>;

}
}
}

#endif
