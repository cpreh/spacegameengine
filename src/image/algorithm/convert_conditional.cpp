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


#include <sge/image/algorithm/convert_conditional.hpp>
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image/size_type.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/optional_impl.hpp>
#include <sge/text.hpp>
#include <sge/exception.hpp>
#include <boost/spirit/home/phoenix/bind/bind_function.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/comparison.hpp>
#include <algorithm>

void
sge::image::algorithm::convert_conditional(
	raw_pointer const data,
	dim_type const &dim,
	color::format::type const fmt,
	size_type const pitch,
	accepted_format_array const &formats)
{
	if(std::find(formats.begin(), formats.end(), fmt) != formats.end())
		return;

	size_type const stride(
		color::format_stride(
			fmt
		)
	);

	accepted_format_array::const_iterator const it(
		std::find_if(
			formats.begin(),
			formats.end(),
			boost::phoenix::bind(
				&color::format_stride,
				boost::phoenix::arg_names::arg1
			)
			== stride
		)
	);

	if(it == formats.end())
		throw exception(
			SGE_TEXT("No suitable color format in convert_conditional!"));

	copy_and_convert(
		view::make_const(
			view::make(
				data,
				dim,
				fmt,
				pitch
			)
		),
		view::make(
			data,
			dim,
			*it,
			pitch
		)
	);
}
