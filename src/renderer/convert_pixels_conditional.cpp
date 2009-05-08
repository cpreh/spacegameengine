/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#include <sge/renderer/convert_pixels_conditional.hpp>
#include <sge/renderer/make_image_view.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/color_format_stride.hpp>
#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <boost/spirit/home/phoenix/bind/bind_function.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/comparison.hpp>
#include <algorithm>

void sge::renderer::convert_pixels_conditional(
	unsigned char *const data,
	dim_type const &dim,
	color_format::type const fmt,
	size_type const pitch,
	accepted_color_format_array const &formats)
{
	if(std::find(formats.begin(), formats.end(), fmt) != formats.end())
		return;
	
	size_type const stride(
		color_format_stride(
			fmt));
	
	accepted_color_format_array::const_iterator const it(
		std::find_if(
			formats.begin(),
			formats.end(),
			boost::phoenix::bind(
				&color_format_stride,
				boost::phoenix::arg_names::arg1
			)
			== stride
		)
	);
	
	if(it == formats.end())
		throw exception(
			SGE_TEXT("No suitable color format in convert_pixels_conditional!"));
	
	copy_and_convert_pixels(
		make_const_image_view(
			make_image_view(
				data,
				dim,
				fmt,
				pitch
			)
		),
		make_image_view(
			data,
			dim,
			*it,
			pitch
		)
	);
}
