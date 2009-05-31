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



#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/variant/apply_binary.hpp>
#include <sge/variant/object_impl.hpp>
#include <boost/gil/algorithm.hpp>

namespace
{

class visitor {
public:
	typedef void result_type;

	visitor();

	template<
		typename V1,
		typename V2
	>
	result_type
	operator()(
		V1 const &src,
		V2 const &dst) const;

	template<
		typename V
	>
	result_type
	operator()(
		V const &src,
		V const &dst) const;
private:
	boost::gil::default_color_converter const converter;
};

}

void sge::image::algorithm::copy_and_convert(
	view::const_object const &src,
	view::object const &dest)
{
	variant::apply_binary(
		visitor(),
		src,
		dest
	);
}

namespace
{


template<
	typename V1,
	typename V2
>
visitor::result_type
visitor::operator()(
	V1 const &src,
	V2 const &dst) const
{
	// hack this because GIL thinks that two views
	// don't need any conversion if they have the same set of channels
	// which are in different order
	return boost::gil::copy_pixels(
		boost::gil::color_converted_view<
			typename V2::value_type
		>(
			src,
			converter
		),
		dst
	);
}

visitor::visitor()
:
	converter()
{}

template<
	typename V
>
visitor::result_type
visitor::operator()(
	V const &src,
	V const &dst) const
{
	return boost::gil::copy_pixels(
		src,
		dst
	);
}

}
