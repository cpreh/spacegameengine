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


#ifndef SGE_IMAGE_IMPL_ALGORITHM_PRINT_IMPL_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_PRINT_IMPL_HPP_INCLUDED

#include <sge/image/mizuiro_color.hpp>
#include <sge/image/algorithm/print.hpp>
#include <sge/image/traits/const_view_fwd.hpp>
#include <mizuiro/color/output.hpp>
#include <mizuiro/image/algorithm/print.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/variant/apply_unary.hpp>


template<
	typename Tag
>
void
sge::image::algorithm::print(
	fcppt::io::ostream &_ostream,
	typename
	sge::image::traits::const_view<
		Tag
	>::type const &_view
)
{
	fcppt::variant::apply_unary(
		[
			&_ostream
		](
			auto const &_view_inner
		)
		{
			mizuiro::image::algorithm::print(
				_ostream,
				_view_inner
			);
		},
		_view.get()
	);
}

#endif
