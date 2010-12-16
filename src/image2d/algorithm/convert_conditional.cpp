/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image2d/algorithm/convert_conditional.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image/size_type.hpp>
#include <sge/image/exception.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <boost/spirit/home/phoenix/bind/bind_function.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <boost/spirit/home/phoenix/operator/comparison.hpp>
#include <algorithm>

void
sge::image2d::algorithm::convert_conditional(
	image::raw_pointer const _data,
	image2d::dim const &_dim,
	image::color::format::type const _format,
	image2d::pitch const _pitch,
	algorithm::accepted_format_array const &_formats
)
{
	if(
		std::find(
			_formats.begin(),
			_formats.end(),
			_format
		)
		!= _formats.end()
	)
		return;

	image::size_type const stride(
		image::color::format_stride(
			_format
		)
	);

	accepted_format_array::const_iterator const it(
		std::find_if(
			_formats.begin(),
			_formats.end(),
			boost::phoenix::bind(
				&image::color::format_stride,
				boost::phoenix::arg_names::arg1
			)
			== stride
		)
	);

	if(
		it == _formats.end()
	)
		throw sge::image::exception(
			FCPPT_TEXT("No suitable color format in convert_conditional!")
		);

	image2d::algorithm::copy_and_convert(
		view::make_const(
			view::make(
				_data,
				_dim,
				_format,
				_pitch
			)
		),
		view::make(
			_data,
			_dim,
			*it,
			_pitch
		)
	);
}
