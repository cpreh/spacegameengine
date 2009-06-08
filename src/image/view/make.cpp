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


#include <sge/image/view/make.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/image/view/impl/fold_format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/optional_impl.hpp>
#include <boost/gil/image_view_factory.hpp>

namespace
{

class operation {
public:
	typedef sge::image::view::object result_type;

	operation(
		sge::image::raw_pointer data,
		sge::image::dim_type const &,
		sge::image::size_type stride,
		sge::image::view::optional_pitch const &pitch);
	
	template<
		typename T
	>
	sge::image::view::object const
	operator()() const;
private:
	sge::image::raw_pointer const data;
	sge::image::dim_type const d;
	sge::image::size_type const stride;
	sge::image::view::optional_pitch const pitch;
};

}

sge::image::view::object const
sge::image::view::make(
	raw_pointer const data,
	dim_type const &d,
	color::format::type const format,
	optional_pitch const pitch)
{
	// TODO: replace this with another mpl algorithm!
	return impl::fold_format(
		operation(
			data,
			d,
			color::format_stride(
				format
			),
			pitch
		),
		format
	);
}

sge::image::view::const_object const
sge::image::view::make(
	const_raw_pointer const data,
	dim_type const &d,
	color::format::type const format,
	view::optional_pitch const pitch)
{
	return make_const(
		make(
			const_cast<
				raw_pointer
			>(
				data
			),
			d,
			format,
			pitch
		)
	);
}

namespace
{

operation::operation(
	sge::image::raw_pointer const data,
	sge::image::dim_type const &d,
	sge::image::size_type const stride,
	sge::image::view::optional_pitch const &pitch)
:
	data(data),
	d(d),
	stride(stride),
	pitch(pitch)
{}

template<
	typename T
>
sge::image::view::object const
operation::operator()() const
{
	return sge::image::view::object(
		boost::gil::interleaved_view(
			d.w(),
			d.h(),
			reinterpret_cast<
				typename T::value_type::value_type *
			>(
				data
			),
			pitch
			? *pitch
			: d.w() * stride
		)
	);
}

}
