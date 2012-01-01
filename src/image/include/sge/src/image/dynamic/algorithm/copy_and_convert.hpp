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


#ifndef SGE_SRC_IMAGE_DYNAMIC_ALGORITHM_COPY_AND_CONVERT_HPP_INCLUDED
#define SGE_SRC_IMAGE_DYNAMIC_ALGORITHM_COPY_AND_CONVERT_HPP_INCLUDED

#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/traits/const_view.hpp>
#include <sge/image/traits/dim.hpp>
#include <sge/image/traits/view.hpp>
#include <sge/src/image/dynamic/algorithm/cac/visitor.hpp>
#include <sge/src/image/dynamic/color/access.hpp>
#include <sge/src/image/dynamic/view/from_static_visitor.hpp>
#include <mizuiro/const_tag.hpp>
#include <mizuiro/nonconst_tag.hpp>
#include <fcppt/math/dim/basic_decl.hpp>
#include <fcppt/variant/apply_binary.hpp>
#include <fcppt/variant/apply_unary.hpp>


namespace sge
{
namespace image
{
namespace dynamic
{
namespace algorithm
{

template<
	typename Tag
>
void
copy_and_convert(
	typename image::traits::const_view<
		Tag
	>::type const &_source,
	typename image::traits::view<
		Tag
	>::type const &_dest,
	image::algorithm::may_overlap::type const _overlap
)
{
	typedef typename image::traits::dim<
		Tag
	>::type::dim_wrapper dim_wrapper;

	fcppt::variant::apply_binary(
		dynamic::algorithm::cac::visitor(
			_overlap
		),
		fcppt::variant::apply_unary(
			dynamic::view::from_static_visitor<
				dim_wrapper::value,
				mizuiro::const_tag
			>(),
			_source.get()
		),
		fcppt::variant::apply_unary(
			dynamic::view::from_static_visitor<
				dim_wrapper::value,
				mizuiro::nonconst_tag
			>(),
			_dest.get()
		)
	);
}

}
}
}
}

#endif
