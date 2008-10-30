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


#include <sge/renderer/make_image_view.hpp>
#include <sge/renderer/make_const_image_view.hpp>
#include <sge/renderer/color_format_stride.hpp>
#include <sge/renderer/detail/fold_color_format.hpp>
#include <boost/gil/image_view_factory.hpp>

namespace
{
struct operation {
	typedef sge::renderer::image_view result_type;

	operation(
		unsigned char *data,
		sge::renderer::dim_type const &,
		sge::renderer::size_type stride,
		sge::renderer::optional_image_pitch const &pitch);
	
	template<
		typename T
	>
	sge::renderer::image_view const
	operator()() const;
private:
	unsigned char *const data;
	sge::renderer::dim_type const d;
	sge::renderer::size_type const stride;
	sge::renderer::optional_image_pitch const pitch;
};

}

sge::renderer::image_view const
sge::renderer::make_image_view(
	unsigned char * const data,
	dim_type const &d,
	color_format::type const format,
	optional_image_pitch const pitch)
{
	return fold_color_format(
		operation(
			data,
			d,
			color_format_stride(
				format),
			pitch),
		format); } 
sge::renderer::const_image_view const
sge::renderer::make_image_view(
	unsigned char const * const data,
	dim_type const &d,
	color_format::type const format,
	optional_image_pitch const pitch)
{
	return make_const_image_view(
		make_image_view(
			const_cast<unsigned char *>(data),
			d,
			format,
			pitch));
}

namespace
{

operation::operation(
	unsigned char *const data,
	sge::renderer::dim_type const &d,
	sge::renderer::size_type const stride,
	sge::renderer::optional_image_pitch const &pitch)
:
	data(data),
	d(d),
	stride(stride),
	pitch(pitch)
{}

template<
	typename T
>
sge::renderer::image_view const
operation::operator()() const
{
	return sge::renderer::image_view(
		boost::gil::interleaved_view(
			d.w(),
			d.h(),
			reinterpret_cast<
				typename T::value_type *>(
				data),
			pitch
			? *pitch
			: d.w() * stride));

}

}
