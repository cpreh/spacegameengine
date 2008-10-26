/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_DETAIL_FOLD_COLOR_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_DETAIL_FOLD_COLOR_FORMAT_HPP_INCLUDED

#include "../image_view.hpp"
#include "../color_format.hpp"
#include "fold_color_format_operation.hpp"
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/container/vector.hpp>

namespace sge
{
namespace renderer
{

template<
	typename Operation
>
typename Operation::result_type
fold_color_format(
	Operation const &op,
	color_format::type const fmt)
{
	// TODO: merge this with the mpl vector!
	typedef boost::fusion::vector<
		rgba8_view,
		argb8_view,
		bgra8_view,
		rgba_f32_view
	> fusion_elements;

	fusion_elements e;

	return boost::fusion::fold(
		e,
		typename Operation::result_type(),
		fold_color_format_operation<
			Operation
			>(
				op,
				fmt));
}

}
}

#endif
