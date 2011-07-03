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


#ifndef SGE_IMAGE_DYNAMIC_ALGORITHM_COPY_AND_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_DYNAMIC_ALGORITHM_COPY_AND_CONVERT_HPP_INCLUDED

#include "copy_and_convert_visitor.hpp"
#include "../view/from_static_visitor.hpp"
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
	typename Source,
	typename Dest
>
void
copy_and_convert(
	Source const &_source,
	Dest const &_dest
)
{
	fcppt::variant::apply_binary(
		dynamic::algorithm::copy_and_convert_visitor(),
		fcppt::variant::apply_unary(
			dynamic::view::from_static_visitor<
				Source::dim_type::static_size,
				typename Source::constness
			>(),
			_source
		),
		fcppt::variant::apply_unary(
			dynamic::view::from_static_visitor<
				Dest::dim_type::static_size,
				typename Dest::constness
			>(),
			_dest
		)
	);
}

}
}
}
}

#endif
