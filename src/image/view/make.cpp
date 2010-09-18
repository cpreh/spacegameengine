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


#include "../convert_dim.hpp"
#include <sge/image/view/make.hpp>
#include <sge/image/view/make_const.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/mpl/invoke_on.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/optional_impl.hpp>
#include <mizuiro/image/is_raw_view.hpp>
#include <boost/mpl/filter_view.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/quote.hpp>

namespace
{

class operation
{
	FCPPT_NONASSIGNABLE(
		operation
	)
public:
	typedef sge::image::view::object result_type;

	operation(
		sge::image::raw_pointer data,
		sge::image::dim_type const &,
		sge::image::view::optional_pitch const &pitch
	);

	template<
		typename View
	>
	sge::image::view::object const
	operator()() const;
private:
	sge::image::raw_pointer const data;
	sge::image::dim_type const dim;
	sge::image::view::optional_pitch const pitch;
};

}

sge::image::view::object const
sge::image::view::make(
	raw_pointer const data,
	dim_type const &d,
	color::format::type const format,
	optional_pitch const pitch
)
{

	// TODO: gcc-4.5: Check if this is a gcc bug

	return fcppt::mpl::invoke_on<
		boost::mpl::filter_view<
			elements,
			boost::mpl::bind<
				boost::mpl::quote1<
					mizuiro::image::is_raw_view
				>,
				boost::mpl::_1
			>
		>
	>(
		static_cast<
			size_type
		>(
			format
		),
		operation(
			data,
			d,
			pitch
		)
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
	sge::image::dim_type const &dim,
	sge::image::view::optional_pitch const &pitch
)
:
	data(data),
	dim(dim),
	pitch(pitch)
{}

template<
	typename View
>
sge::image::view::object const
operation::operator()() const
{
	return sge::image::view::object(
		View(
			sge::image::convert_dim<
				typename View::dim_type
			>(
				dim
			),
			data,
			typename View::pitch_type(
				pitch
				? *pitch
				: 0
			)
		)
	);
}

}
