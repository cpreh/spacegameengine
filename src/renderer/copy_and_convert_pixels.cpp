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



#include <sge/renderer/copy_and_convert_pixels.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>
#include <boost/gil/algorithm.hpp>

namespace
{

template<
	typename CC
>
class copy_and_convert_pixels_fn
: public boost::gil::binary_operation_obj<
	copy_and_convert_pixels_fn<
		CC
	>
> {
private:
	CC const cc;
public:
	typedef typename boost::gil::binary_operation_obj<
		copy_and_convert_pixels_fn<
			CC
		>
	>::result_type result_type;

	copy_and_convert_pixels_fn()
	:
		cc()
	{}

	explicit copy_and_convert_pixels_fn(
		CC const cc)
	:
		cc(cc)
	{}

	template<
		typename V1,
		typename V2
	>
	result_type
	apply_incompatible(
		V1 const &src,
		V2 const &dst) const
	{
		return boost::gil::copy_pixels(
			boost::gil::color_converted_view<
				typename V2::value_type
			>(
				src,
				cc),
			dst);
	}

	template<
		typename V1,
		typename V2
	>
	result_type
	apply_compatible(
		V1 const &src,
		V2 const &dst) const
	{
		// hack this because GIL thinks that two views
		// don't need any conversion if they have the same set of channels
		// which are in different order
		return apply_incompatible(
			src,
			dst);
	}

	template<
		typename V
	>
	result_type
	apply_compatible(
		V const &src,
		V const &dst) const
	{
		return boost::gil::copy_pixels(
			src,
			dst);
	}
};

}

void sge::renderer::copy_and_convert_pixels(
	const_image_view const &src,
	image_view const &dest)
{
        boost::gil::apply_operation(
		src,
		dest,
		copy_and_convert_pixels_fn<
			boost::gil::default_color_converter
		>());
}
