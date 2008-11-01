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


#include <sge/renderer/convert_pixels_conditional.hpp>
#include <sge/renderer/image_view_format.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/color_format_stride.hpp>
#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <algorithm>

void sge::renderer::convert_pixels_conditional(
	image_view const &view,
	accepted_color_format_array const &formats)
{
	color_format::type const fmt(
		image_view_format(
			make_const_image_view(
				view)));
	
	if(std::find(formats.begin(), formats.end(), fmt) != formats.end())
		return;
	
	size_type const stride(
		color_format_stride(
			fmt));
	
	accepted_color_format_array::const_iterator const it(
		std::find_if(
			formats.begin(),
			formats.end(),
			boost::lambda::bind(
				&color_format_stride,
				boost::lambda::_1)
			== stride));
	
	if(it == formats.end())
		throw exception(
			SGE_TEXT("No suitable color format in convert_pixels_conditional!"));
	
	//copy_and_convert_pixels(
	//	view);
}
