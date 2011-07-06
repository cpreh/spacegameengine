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


#ifndef SGE_IMAGE_DYNAMIC_ALGORITHM_CAC_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_DYNAMIC_ALGORITHM_CAC_CONVERT_HPP_INCLUDED

#include "choose.hpp"
#include "convert_visitor.hpp"
#include "function.hpp"
#include <mizuiro/image/algorithm/detail/apply_binary_iteration.hpp> // TODO
#include <mizuiro/detail/variant_apply_binary.hpp> // TODO

namespace sge
{
namespace image
{
namespace dynamic
{
namespace algorithm
{
namespace cac
{

template<
	typename Source,
	typename Dest
>
void
convert(
	Source const &_source,
	Dest const &_dest
)
{
	mizuiro::detail::variant_apply_binary(
		mizuiro::image::algorithm::detail::apply_binary_iteration(
			cac::convert_visitor<
				typename cac::function<
					typename Source::format,
					typename Dest::format
				>::type
			>(
				cac::choose(
					*_source.format_store().get(),
					*_dest.format_store().get()
				)
			)
		),
		_source.range(),
		_dest.range()
	);
}

}
}
}
}
}

#endif
